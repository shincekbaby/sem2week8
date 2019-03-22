#include <iostream>
using namespace std;

class Node 
{
	public:
	int data;
	Node *parent, *left, *right;
	Node(int val)
	{parent=NULL;left=NULL;right=NULL;data=val;}
};

class Btree
{
	
	public:
	Node *root;
	int c;
	Btree()
	{root = NULL;c=0;}	
	//void insert(int value);
	void insert(Node *curr, int value);
	void display(Node *curr,int space);
	Node *search(int val);
	Node *find_min(Node *curr);
	int count();
	void replace(Node *curr, Node *rep);
	void del(int data);
	int range_search(int k, int l);
	int height(Node *ptr);
	Node *getroot()
	{return root;}
};

void Btree::insert(Node *curr,int value)
{
	if(root==NULL)
	{root= new Node(value);++c;}
	
	else if(value<curr->data)
	{
		if(curr->left==NULL)
		{curr->left=new Node(value);curr->left->parent=curr;++c;}
		
		else	
		insert(curr->left,value);
	}
	
	else if(value>curr->data)
	{
		if(curr->right==NULL)
		{curr->right=new Node(value);curr->right->parent=curr;++c;}
		
		else	
		insert(curr->right,value);
	}

	else
	return;
}

void Btree::display(Node *curr , int space)
{
	if(curr->right!=NULL)
	{display(curr->right,space+1);}

	for(int i=space; i>0;i--)
	cout<<"   ";
	
	cout<<curr->data<<"\n";	
	
	if(curr->left!=NULL)
	{display(curr->left,space+1);}
}	

Node *Btree::search(int val)
{
	Node *ptr=root;	
	while(ptr!=NULL)
	{
		if(ptr->data==val)
		return ptr;
		
		else if(ptr->data > val)
		ptr=ptr->left;
		
		else
		ptr=ptr->right;
	 }
	return ptr;
}

Node *Btree::find_min(Node *curr)
{
	while(curr->left!=NULL)
	curr=curr->left;
	
	return curr;
}

int Btree::count()
{
	return c;	
}

void Btree::replace(Node *curr, Node *rep)
{
	Node *par=curr->parent;
	if(curr!=root)
	{
		if(curr==par->left)
		{par->left=rep;}
		else if(curr==par->right)
		{par->right=rep;}
		rep->parent=curr->parent;
	}
	else if(curr==root)
	{
		root=rep;
		rep->left=curr->left;
		rep->left->parent=rep;
		
		if(rep->parent!=curr)		
		{
			if(rep->right)
			replace(rep,rep->right);
		
			else
			{rep->parent->left=NULL;}
		 		
			rep->right=curr->right;
			rep->right->parent=rep;
		}
		rep->parent=NULL;
		
	}
}

void Btree::del(int val)
{
	Node *curr=search(val);
	Node *ptr=find_min(curr->right);
	replace(curr,ptr);
	delete curr;
}

int Btree::height(Node *ptr)
{
	if(ptr==NULL)
	return 0;
	
	int lh=height(ptr->left), rh=height(ptr->right);
	
	if(lh>rh)
	return lh+1;
	
	else
	return rh+1;
}

int Btree::range_search(int k, int l)
{
	Node *ptr=search(k), *ptr2=search(l);
	int c=0;
	
	if(ptr!=NULL && ptr2!=NULL)
	while(ptr!=ptr2)
	{
		cout<<ptr->data<<",";
		if(ptr->parent)		
		{if(ptr->parent->left==ptr)
		 {if(ptr->parent->data <= l)
		  ptr=ptr->parent;++c;}}
		
		else{ptr=ptr->right;++c;}
	}
	cout<<l<<" DONE";
	return c+1;
}

int main()
{
	Btree b;
	b.insert(b.getroot(),4);
	b.insert(b.getroot(),3);
	b.insert(b.getroot(),2);
	b.insert(b.getroot(),1);
	b.insert(b.getroot(),6);
	b.insert(b.getroot(),7);
	b.insert(b.getroot(),5);
	b.insert(b.getroot(),9);
	
	b.display(b.getroot(),0);
	
	cout<<"-------------------------------------------------------------"<<endl;
	cout<<"Minimum value = "<<b.find_min(b.root)->data<<endl;
	cout<<"no of nodes = "<<b.count()<<endl;
	b.del(4);
	b.display(b.getroot(),0);
	cout<<"-------------------------------------------------------------"<<endl;
	b.del(5);
	b.display(b.getroot(),0);
	cout<<"-------------------------------------------------------------"<<endl;
	cout<<"Height = "<<b.height(b.getroot())<<endl;
	
	cout<<b.range_search(2,7)<<endl;
	return 0;
}
