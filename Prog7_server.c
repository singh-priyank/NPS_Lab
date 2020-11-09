// =====================================================================================
//
//       Filename:  server.c
//
//    Description:  NPS lab program 7
//
//        Version:  1.0
//       Revision:  none
//       Compiler:  g++
//
//   Organization:  RVCE Bangalore
//
// =====================================================================================


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>

#define PORT 8080


int main(int argc, char const *argv[]) 
{
    int sd,acpt,len,bytes,port;
    char send[50],receiv[50];
    struct sockaddr_in serv,cli;
    if((sd=socket(AF_INET,SOCK_STREAM,0))<0) { 
        printf("Error in socket\n"); 
        exit(0); 
    }
    bzero(&serv,sizeof(serv)); 
    printf("Enter the port number : "); 
    scanf("%d",&port); serv.sin_family=AF_INET; 
    serv.sin_port=htons(port); 
    serv.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sd,(struct sockaddr *)&serv,sizeof(serv))<0) { 
        printf("Error in bind\n"); exit(0);
    }

    if(listen(sd,3)<0) { 
	printf("Error in listen\n"); exit(0); 
    } 
    if((acpt=accept(sd,(struct sockaddr*)NULL,NULL))<0) { 
	printf("\n\t Error in accept"); exit(0); 
    }


    while(1)
    {
	bytes=recv(acpt,receiv,50,0);
    	receiv[bytes]='\0';
        if(strcmp(receiv ,"exit")==0){
	    	close(acpt);
    		close(sd); exit(0);
    	}
    	else{
	    	printf("Command received : %s",receiv);
	    	system(receiv);
	    	printf("\n");
	    }
    } 

    return 0;
}
