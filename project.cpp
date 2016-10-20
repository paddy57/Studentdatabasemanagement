#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
struct node
{
    char employee_name[100],employee_address[100],designation[100];
    int employee_number;
	struct node *left;
    struct node *right;
    int height;
};
struct dbnode
{
    char employee_name[100],employee_address[100],designation[100];
    int employee_number;
};
int flag,count,temp;

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

struct node* newNode(struct dbnode db)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    strcpy(node->employee_name,db.employee_name);
    strcpy(node->employee_address,db.employee_address);
    strcpy(node->employee_address,db.employee_address);
    node->employee_number=db.employee_number;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}

struct node *rightRotate(struct node *p)
{
    struct node *temp = p->left;
    p->left=temp->right;
    temp->right=p;

    p->height = max(height(p->left), height(p->right))+1;
    temp->height = max(height(temp->left), height(temp->right))+1;

    return temp;
}

struct node *leftRotate(struct node *p)
{
    struct node *temp=p->right;
    p->right=temp->left;
    temp->left=p;

    p->height = max(height(p->left), height(p->right))+1;
    temp->height = max(height(temp->left), height(temp->right))+1;

    return temp;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node,struct dbnode db)
{
    if (node == NULL)
        return(newNode(db));
    
	if (db.employee_number < node->employee_number)
        node->left  = insert(node->left,db);
    else if(db.employee_number > node->employee_number)
        node->right = insert(node->right,db);
    else
    {
    	temp=1;
    	strcpy(node->employee_name,db.employee_name);
        strcpy(node->employee_address,db.employee_address);
        strcpy(node->employee_address,db.employee_address);
        node->employee_number=db.employee_number;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && db.employee_number < node->left->employee_number)
        return rightRotate(node);

    if (balance < -1 && db.employee_number > node->right->employee_number)
        return leftRotate(node);

    if (balance > 1 && db.employee_number > node->left->employee_number)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && db.employee_number < node->right->employee_number)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void print(struct node *root)
{
    if(root != NULL)
    {
	    print(root->left);
		printf("employee number =>%d\n",root->employee_number);
	    printf("employee name   =>%s\n",root->employee_name);
	    printf("project name    =>%s\n",root->employee_address);
		printf("___________________________________________________________________\n");
		print(root->right);
    }
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    while (current->left != NULL)
        current = current->left;
 
    return current;
}

struct node* deleteNode(struct node* root,int employee_number)
{
    if (root == NULL)
        return root;

    if (employee_number < root->employee_number)
        root->left = deleteNode(root->left,employee_number);
 
    else if(employee_number > root->employee_number)
        root->right = deleteNode(root->right,employee_number);

    else
    {
        if((root->left == NULL) || (root->right == NULL))
        {
            struct node *temp = root->left ? root->left : root->right;
 
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
 
            free(temp);
            printf("DELETED\n");
            flag=1;
        }
        else
        {
            struct node* temp = minValueNode(root->right);
            strcpy(root->employee_name,temp->employee_name);
			strcpy(root->employee_address,temp->employee_address);
			root->employee_number=temp->employee_number;
			employee_number=temp->employee_number;
            root->right = deleteNode(root->right,employee_number);
        }
    }
    if (root == NULL)
      return root;
    
    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}


struct node * search(struct node *root,struct dbnode db)
{
	if (root == NULL)
        {
		printf("entry not found\n");
        return 0;
        }

    if (db.employee_number < root->employee_number)
        root->left = search(root->left,db);
 
    else if(db.employee_number > root->employee_number)
        root->right = search(root->right,db);
    
	else
	    {
	    	printf("employee number =>%d\n",root->employee_number);
	    	printf("employee name   =>%s\n",root->employee_name);
	    	printf("project name    => %s\n",root->employee_address);
	    	printf("___________________________________________________________________\n");
	    	return 0;
	    }
}

int getnumrecords(struct node * root)
{
	if(root != NULL)
    {
    	count++;
	    getnumrecords(root->left);
        getnumrecords(root->right);
    }
}


void rangesearch(struct node *root, int min, int max)
{
   if (root==NULL)
      return;

   if (root->employee_number>=min && root->employee_number<=max)
   {
   	   rangesearch(root->left,min,max);
	   printf("employee number =>%d\n",root->employee_number);
	   printf("employee name   =>%s\n",root->employee_name);
	   printf("project name    =>%s\n",root->employee_address);
	   printf("___________________________________________________________________\n");
	   rangesearch(root->right,min,max);
   }
   if(root->employee_number<min)
   {
   	   if(root->right!=NULL)
   	       rangesearch(root->right,min,max);
   }
   if(root->employee_number>max)
   {
   	   if(root->left!=NULL)
   	       rangesearch(root->left,min,max);
   }
   return;
}
 

int main()
{
  struct node *root = NULL;
  struct dbnode db;
  int a,b,ch,min,max,n;
  char employee_name[100],employee_address[100],ch1[100],ch2[100];
  int employee_number;
  FILE *fp;
  fp = fopen("db1.txt","r");
  root=NULL;
  do 
  {
    printf("1. Insertion\n2. Deletion\n3. Height\n4. Searching\n5. No of active records\n6. Range search \n7. Print\nEnter your choice:\n");
    scanf("%d", &ch);
    switch (ch) 
		{
                    case 1: 
			        while(fscanf(fp,"%d",&n)==1)
                    {
					    temp=0;
                        fscanf(fp,"%s%s",ch1,ch2);
                        db.employee_number=n;
                        strcpy(db.employee_name,ch1);
                        strcpy(db.employee_address,ch2);
                        root=insert(root,db);
                                if(temp==0)
                                   printf("inserted\n");
                                else
                                   printf("updated\n");
                                printf("___________________________________________________________________\n");
					}
                                break;
                    
                    case 2:
                        	    flag=0;
                                printf("Enter the employee number:\n");
								scanf("%d",&employee_number);
								root=deleteNode(root,employee_number);
                                if(flag==0)
                                   printf("data not found\n");
                                printf("___________________________________________________________________\n");
                                break;
                    case 3:
                            	b=height(root);
                            	printf("height of the tree is %d\n",b);
                            	printf("___________________________________________________________________\n");
                            	break;
                    case 4:
                        	    printf("Enter the key value to search:\n");
                                scanf("%d",&db.employee_number);;
                                search(root,db);
                                break;
					case 5:
                        	    count=0;
                                getnumrecords(root);
                                printf("no of active records is %d\n",count);
                                printf("___________________________________________________________________\n");
								break;
					case 6:
							    printf("enter the limits\n");
							    scanf("%d%d",&min,&max);
							    rangesearch(root,min,max);
							    break;
					case 7:
                                print(root);
                                break;
                }
            printf("Enter 1 if you want to continue\n");
            scanf("%d",&a);
    }
	while(a==1);
	fclose (fp);
}
 
