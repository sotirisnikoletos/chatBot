/* Manvir Singh
   AM : 2022201600155
   dit16155@uop.gr
   
   Sotiris Nikoletos
   AM : 2022201600124
   dit16124@uop.gr
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define yes 1
#define no 0

//default struct (ECLASS),can add more,not delete/edit those 5
typedef struct cList{
		char *concept;//the concept learned
		char *sentence;//the sentence assoc. with the concept
		int timesUsed;//no. of times the concept was used to an answer
		char learnedFrom[5];//learned either from file or keyboard
		struct cList *next;
		
}conceptList;
void load();//loading screen
void show(conceptList *c1,FILE *test,int know,char* con);
int search (conceptList *head,char *concept);
int question(conceptList *head, char *concept);
conceptList *delete (conceptList *head, char *concept,int * empty);
conceptList *insert(conceptList *h,conceptList  *t);

int main(void)
{
	FILE *test;
	int i, j = 0, len = 0, kena = 0, know, empty = 0 , num;
	conceptList *c1=NULL,*head=NULL,*temp=NULL;
	static cnt = 0;
	int choice;
	char *str, *token, *con = NULL, *sen = NULL;
 	srand(time(NULL));
 	
	 
	load();
 	
	 
	 
	if(fopen("dialogue.txt","w+")==NULL){
		printf("Error opening file!\n");
	}
	test=fopen("dialogue.txt","a+");
	fprintf(test,"Welcome dude!\nWanna chat with me (1) or Exit (2) ?\n");
 	printf("Welcome dude!\nWanna chat with me (1) or Exit (2) ?\n");
	scanf("%d",&choice);
	fprintf(test,"%d",choice);
	while(getchar()!='\n');
	if(choice==2)
	{
		fprintf(test,"3B$ You are such a loser !!!\n");
		printf("\n3B$ You are such a loser !!!\n");
	}
	else{
		printf("\n3B$ Say something!\n");
		fprintf(test,"\n3B$ Say something!\n");
		while(1){
			con = NULL;
			sen = NULL;
			kena = 0;
			fprintf(test, "me$ ");
			printf("me$ ");
			str = (char*)malloc(600 * sizeof(char));
			gets(str);

			fputs(str, test);
			if(strcmp(str,"Fish")==0){
				printf("3B$ Bye bye! Cu soon...\n");
				fprintf(test,"3B$ Bye bye! Cu soon...\n");
				break;
			}
			else if (strncmp(str, "learn this > ", 13) == 0)
			{
				if (c1 != NULL){
					con = strtok(str, " ");
					for (i = 0; i < 2; i++){
						con = strtok(NULL, " ");
					}
					con = strtok(NULL, ":");
					sen = strtok(NULL, "\0");
					know = search(head, con);
				}
				else if (c1 == NULL){
					know = 0;
				}
				if (know == no){
					c1 = insert(head, c1);
					token = strtok(str, " ");
					if (con != NULL){
						c1->concept = con;
					}
					else{
						while (1){
							kena++;
							if (kena == 3){
								c1->concept = strtok(NULL, ":");
								break;
							}
							token = strtok(NULL, " ");
						}
					}
					if (sen == NULL){
						c1->sentence = strtok(NULL, "\0");
					}
					else
					{
						c1->sentence = sen;
					}
					strcpy(c1->learnedFrom, "kbrd");
					c1->timesUsed = 0;
					if (cnt == 0){
						head = c1;
						cnt++;
					}
					show(c1, test, know,con);
				}
				else if (know == yes){
					show(c1, test, know,con);
				}
			}
else if (strncmp(str, "forget this > ", 14) == 0){
				token = strtok(str, " ");
				for (i = 0; i < 2; i++){
					token = strtok(NULL, " ");
				}
				con = strtok(NULL, "\0");
				head = delete(head, con,&empty);
				num = rand() % 5+1;
				if (empty == 0 && head==NULL){
					printf("3B$ ");
					switch (num){
					case(1) :
						printf("What the h*** is %s ?\n", con);
						fprintf(test,"What the h*** is %s ?\n", con);
						break;
					case(2) :
						printf("Hmm,I am confused now ! How can I forget something that I have no clue of ?\n");
						fprintf(test,"Hmm,I am confused now ! How can I forget something that I have no clue of ?\n");
						break;
					case(3) :
						printf("What is this %s ?I have no memory of it !\n", con);
						fprintf(test,"What is this %s ?I have no memory of it !\n", con);
						break;
					case(4) :
						printf("Does %s even exist ? I think that you're trolling me!\n",con);
						fprintf(test,"Does %s even exist ? I think that you're trolling me!\n", con);
						break;
					case(5) :
						printf("Is this %s a person or a thing ? I can't say I recall any of it!\n",con);
						fprintf(test,"Is this %s a person or a thing ? I can't say I recall any of it!\n", con);
						break;
					}
				}
				else if(head!=NULL && empty==0){
					printf("3B$ ");
					switch (num){
					case(1) :
						printf("I feel so nice now that I deleted %s... was a pain in my ***!\n", con);
						fprintf(test, "I feel so nice now that I deleted %s... was a pain in my ***!\n", con);
						break;
					case(2) :
						printf("Well, %s turned out to be a piece of trush, so i ejected it from my memory!\n",con);
						fprintf(test, "Well, %s turned out to be a piece of trush, so i ejected it from my memory!\n",con);
						break;
					case(3) :
						printf("Ok, I erased %s from my system, anything else dude?\n", con);
						fprintf(test, "Ok, I erased %s from my system, anything else dude?\n", con);
						break;
					case(4) :
						printf("All in all,%s was a useless thing to know, we will be more comfortable without it!\n", con);
						fprintf(test, "All in all,%s was a useless thing to know, we will be more comfortable without it!\n", con);
						break;
					case(5) :
						printf("Forget about %s ? Hell yeah dude, ok!\n", con);
						fprintf(test, "Forget about %s ? Hell yeah dude,ok!\n", con);
						break;
					}
				}
			}
			
			else if(strcmp(str,"What is the meaning of Life,The Universe,and Everything?")==0)
			{
			printf("3B$ 42\n");
			fprintf(test,"3B$ 42\n");
			}
			else if(strcmp(str,"What do you know about?")==0){
				temp=head;
				if(temp==NULL){
					printf("3B$ Sorry I know nothing because my memory is empty\n");
					fprintf(test,"3B$ Sorry I know nothing because my memory is empty\n");
				}
				else{
					printf("3B$ All things I know:\n");
					fprintf(test,"3B$ All things I know:\n");
					printf("%s\n", temp->concept);
					fprintf(test, "%s\n", temp->concept);
					temp = temp->next;
					while(temp!=head){
						printf("%s\n",temp->concept);
						fprintf(test,"%s\n",temp->concept);
						temp=temp->next;
					}
				}
			}
			else if(strcmp(str,"What do you talk about?")==0){
				temp=head;
				if(temp==NULL){
					printf("3B$ I don't have something to talk about!\n");
					fprintf(test,"3B$ I dont't have something to talk about!\n");
				}
				else{
					if(temp->timesUsed>0){
						printf("3B$ Things I usually talk about: \n");
						fprintf(test,"3B$ Things I usually talk about: \n");
						while(temp->next!=head){
							if(temp->timesUsed>0){
							printf("%s: ",temp->concept);
							fprintf(test,"%s: ",temp->concept);
							printf("%d times!\n",temp->timesUsed);
							}
							temp=temp->next;
						}
					}
					else
						printf("3B$ Till now nothing to talk!\n");
				}
			}
			else{
				
				token=strstr(str,"?");
				printf("3B$ ");
				if (token == NULL){
					num=rand()%7+1;
					switch (num){
					case(1) :
						printf("Hmm, that sounds interesting!\n");
						fprintf(test,"Hmm, that sounds interesting!\n" );
						break;
					case(2) :
						printf("That's right man!\n");
						fprintf(test, "That's right man!\n");
						break;
					case(3) :
						printf("Tell me more about it, try to be specific...\n");
						fprintf(test,"Tell me more about it, try to be specific...\n");
						break;
					case(4) :
						printf("I see ! Well, that seems to be nice!\n");
						fprintf(test,"I see ! Well, that seems to be nice!\n");
						break;
					case(5) :
						printf("Good for you buddy!\n");
						fprintf(test,"Good for you buddy!\n");
						break;
					case(6):
						printf("That's sounds like a plan.\n");
						fprintf(test,"That's sounds like a plan.\n");
						break;
					case(7) :
						printf("I totally agree with you dude!\n");
						fprintf(test,"I totally agree with you dude!\n");
						break;
					}
				}
				else
				{
					token=strtok(str,"*");
					con=strtok(NULL,"*");
					know=question(head, con);
					if (know == 0){
						num = rand() % 5 + 1;
						switch (num){
						case(1) :
							printf("I know nothing about %s.\n", con);
							fprintf(test, "I know nothing about %s.\n", con);
							break;
						case(2) :
							printf("I can't find anything about %s in my memory!\n", con);
							fprintf(test, "I can't find anything about %s in my memory!\n", con);
							break;
						case(3) :
							printf("I don't have any clue of %s!\n", con);
							fprintf(test,"I don't have any clue of %s!\n", con);
							break;
						case(4) :
							printf("Sorry, but I can't recall anything about %s.\n", con);
							fprintf(test,"Sorry, but I can't recall anything about %s.\n", con);
							break;
						case(5) :
							printf("Not a single idea about what the fish is %s!\n", con);
							fprintf(test,"Not a single idea about what the fish is %s!\n", con);
							break;
						}
					}
				}
			}
		}
			free(str);
			fclose(test);	
	}
 	return 0;
}
conceptList *insert(conceptList *h,conceptList  *t){
	conceptList *new;
	new=(conceptList *)malloc(sizeof(conceptList ));
	if(t==NULL){
		new->next=new;
		return new;
	}
	else{
		t->next=new;
		t=new;
		t->next=h;
		return new;
	}
		
}
void show( conceptList *c1, FILE *test, int know,char* con)
{
	char *tmp=NULL;
	double d;
	int k;
	char str1;
	k = rand()% 9+1;
	fprintf(test,"\n3B$ ");
	printf("3B$ ");
	if (know == 0){
		switch (k){
		case(3) :
			printf("It was interesting learning about %s !\n", c1->concept);
			fprintf(test,"It was interesting learning about %s !\n", c1->concept);
			break;
		case(1) :
			printf("Wow! first time I learn something about %s !\n",c1->concept);
			fprintf(test,"Wow! first time I learn something about %s !\n", c1->concept);
			break;
		case(4) :
			printf("Ok! I have learned about %s. Now let's just move on !\n",c1->concept);
			fprintf(test,"Ok! I have learned about %s.Now let's just move on !\n", c1->concept);
			break;
		case(2) :
			printf("It's always fun learning something new like %s !\n",c1->concept);
			fprintf(test,"It's always fun learning something new like %s !\n", c1->concept);
			break;
		case(5):
			fprintf(test,"Learning about %s was quite easy honestly speaking !\n", c1->concept);
			printf("Learning about %s was quite easy honestly speaking !\n", c1->concept);
			break;
		case(6) :
			printf("That was great.You should have talked to me about %s!\n",c1->concept);
			fprintf(test,"That was great.You should have talked to me about %s!\n",c1->concept);
			break;
		case(7) :
			printf("Hmm,learning about %s was child's play...\n",c1->concept);
			fprintf(test,"Hmm,learning about () was child's play...\n",c1->concept);
			break;
		case(8) :
			printf("Wow, at last something worth learning!\n");
			fprintf(test, "Wow, at last something worth learning!\n");
			break;
		case(9) :
			printf("%s was of huge importance and not awful at all, really! Thanks dude!\n",c1->concept);
			fprintf(test, "%s was of huge importance and not awful at all, really! Thanks dude!\n",c1->concept);
			break;
		}
	}
	else{
		k=rand()% 8+1;
		switch (k){
		case(7) :
			printf("You really expected me not to know about %s ?\n", con);
			fprintf(test, "You really expected me not to know about %s ?\n", con);
			break;
		case(1) :
			printf("Believe me, I already know about %s !\n", con);
			fprintf(test, "Believe me, I already know about %s !\n", con);
			break;
		case(2) :
			printf("You little fellow, I know about %s for a long time now !\n", con);
			fprintf(test, "You little fellow, I know about %s for a long time now !\n", con);
			break;
		case(3) :
			printf("Do you thing I am dump ? I knew about %s before you were even born !\n", con);
			fprintf(test, "Do you thing I am dump ? I knew about %s before you were even born !\n", con);
			break;
		case(4) :
			printf("Thanks for reminding me that I ALREADY know about %s,kid !\n", con);
			fprintf(test, "Thanks for reminding me that I ALREADY know about %s,kid !\n", con);
			break;
		case(5):
			printf("You think I have no idea what %s is? Im not just a machine!\n",con);
			fprintf(test,"You think I have no idea what %s is? Im not just a machine!\n",con);
			break;
		case(6):
			printf("You have mentioned %s before, so try me again!\n",con);
			fprintf(test,"You have mentioned %s before, so try me again!\n",con);
			break;
		case(8):
			printf( "Stop telling me stuff I already know! Come on!\n");
			fprintf(test, "Stop telling me stuff I already know! Come on!\n");
			break;
		}
	}
	return;
}
int search(conceptList *h, char * concept){
	conceptList * tmp;
	tmp = h;
	if (strcmp(tmp->concept, concept) == 0){
		tmp->timesUsed++;
		return 1;
	}
	else{
		while (tmp->next != h){
			if (strcmp(tmp->concept, concept) == 0){
				tmp->timesUsed++;
				return 	1;
			}
			tmp = tmp->next;
		}
	}
	return 0;

}
conceptList *delete (conceptList *h, char *concept,int* empty){
	conceptList *tmp,*prev=NULL;
	tmp=h;
	if (h != NULL)
		prev = h;
	if(tmp==NULL){
		printf("3B$ My memory is empty\n");
		*(empty) = 1;
		return NULL;
	}
	else if(tmp->next==h){
			if(strcmp(tmp->concept,concept)==0){
				tmp->timesUsed ++;
				free(tmp);
				*(empty) = 1;
				return NULL;
			}
	}
	else if (strcmp(tmp->concept, concept) == 0){
		while (tmp->next != h){
			
			tmp = tmp->next;
		}
		prev = tmp;
		tmp = tmp->next;
		prev->next = tmp->next;
		free(tmp);
		h=prev->next;
		return h;
	}
	else{
		while(tmp->next!=h){
			if(strcmp(tmp->concept,concept)==0){
				tmp->timesUsed ++;
				prev->next=tmp->next;
				free(tmp);
				return h;
				break;
			}
			tmp=tmp->next;
		}
	}
	*(empty) = 0;
	return h;
}
int question(conceptList *h, char *concept){
	conceptList *tmp;
	tmp = h;
	if (strcmp(tmp->concept, concept) == 0){
		printf("\b%s\n", tmp->sentence);
		tmp->timesUsed++;
		return 1;
	}
	else{
		if (strcmp(tmp->concept, concept) == 0){
			printf("\b%s\n", tmp->sentence);
			tmp->timesUsed++;
			return 	1;
		}
		tmp = tmp->next;
		while (tmp != h){
			if (strcmp(tmp->concept, concept) == 0){
				printf("\b%s\n", tmp->sentence);
				tmp->timesUsed++;
				return 	1;
			}
			tmp = tmp->next;
		}
	}
	tmp = h;
	if ((strstr(tmp->sentence, concept)) != NULL){
		printf("\b%s\n", tmp->sentence);
		tmp->timesUsed++;
		return 1;
	}
	tmp = tmp->next;
	while (tmp!=h){
		if ((strstr(tmp->sentence, concept)) != NULL){
			printf("\b%s\n", tmp->sentence);
			tmp->timesUsed++;
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;

}
