#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


struct node{
	char data;
	struct node * next;
}*head;

void add( char num )
{
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=num;
    if (head== NULL)
    {
    head=temp;
    head->next=NULL;
    }
    else
    {
    temp->next=head;
    head=temp;
    }
}

 
void  display(struct node *r,int znak,int celo,int stevilo)
{
	char data[stevilo];
	int cifra = stevilo;
	int cifra2 = stevilo - 1;
	int n = 0;
	
	r = head;
	//printf("TEST");
	
	while(r != NULL)
	{
		
		//printf("TEST");
		data[cifra2] = r->data;
		
		r = r->next;
		
		cifra2 = cifra2 - 1;
	}
	if(znak == 1)
	{
	
		for(n = 0; n < stevilo/sizeof(char); n+=1){
			printf("%d\t", data[n]);
		}
		printf("\n");
    
	}
	else if(znak == 0)
	{
		
		for(n = 0; n < stevilo/sizeof(char); n+=1){
			dprintf(celo,"%d ", data[n]);
		}
	}
}

void privzet_vhod(int argc, char *argv[])
{
	struct node *n;
    head=NULL;

	char data1[1];
	
	
	int stevec = 0;
	
	
	while(read(0, data1, sizeof(char)) > 0)
	{
		//data[stevec] = data1[0];
		add(data1[0]);
		stevec = stevec + 1;
	}
	display(n,1,0,stevec);
	
}

void i_preberi(char *argv[])
{
	int n = 0;
	char data1[1] = {};
	
	int oprimek = open(argv[2], O_RDONLY);
	
	int stevec = 0;
	
	
	
	while(read(oprimek, data1, sizeof(char)) > 0)
	{
		stevec = stevec + 1;
	}
	
	char data[stevec];
	int oprimek1 = open(argv[2], O_RDONLY);
	read(oprimek1, data, stevec*sizeof(char));
	
	
	
	for(n = 0; n < stevec/sizeof(char); n+=1){
		printf("%d\t", data[n]);
	}
	printf("\n");
	
}

void o_zapisi(int argc,char *argv[])
{
	char data1[1];
	FILE *fajl;
	open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0660);
	int stevec = 0;
	
	fajl = fopen(argv[2],"w");
	
	while(read(0, data1, sizeof(char)) > 0)
	{
		fprintf(fajl,"%d ",data1[0]);
		stevec = stevec + 1;
	}
	
	fclose(fajl);

	
}

void v_o(int argc,char *argv[])
{
	struct node *no;
    head=NULL;
	
	char data1[1];
	int stevec = 0;
	
	while(read(0, data1, sizeof(char)) > 0)
	{
		//data[stevec] = data1[0];
		add(data1[0]);
		stevec = stevec + 1;
	}
	
	//int op = open(st, O_CREAT|O_WRONLY|O_TRUNC, 0660);
	//dup2(op,st);
	
	
	//write(st,data,stevec*sizeof(char));
	
	int cifra = strtol(argv[2], NULL, 10);
	
	display(no,0,cifra,stevec);
	
}

void v_i(int argc,char *argv[])
{
	int cifra = strtol(argv[2], NULL, 10);
	
	struct node *no;
    head=NULL;
	
	char data1[1];
	int stevec = 0;
	while(read(cifra, data1, sizeof(char)) > 0)
	{
		//data[stevec] = data1[0];
		add(data1[0]);
		stevec = stevec + 1;
	}
	
	display(no,1,0,stevec);
}


int main(int argc, char** argv) {
	
	int o = 0;
	int i = 0;
	int vo = 0;
	int vi = 0;
			
	int opcija;
	
	
	
	while((opcija = getopt(argc, argv, "o:i:O:I:")) != -1)
	{
		switch(opcija)
		{
			case 'o':
				
				o = 1;
				break;
			
			case 'i':
				i = 1;
				o = 0; 
				break;
			
			case 'O':
				vo = 1;
				o = 0;
				i = 0;
				break;
			case 'I':
				vi = 1;
				vo = 0;
				o = 0;
				i = 0;
		}
		
	}
	
	
	if(o == 1)
	{
		o_zapisi(argc,argv);
		
	}
	else if(i == 1)
	{
		i_preberi(argv);
	}
	else if(vo == 1)
	{
		v_o(argc,argv);
	}
	else if(vi == 1)
	{
		v_i(argc,argv);
	}
	else
	{
		privzet_vhod(argc,argv);
	}
		
	
	return 0;
}
