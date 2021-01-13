// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 28
int h = 0;
int a = 0;
int s = 0;

double n = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N - 2][N][N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
   int st=strlen(word);
   h = tolower(word[0]) % ('a');

   if(st>1)
   { a = tolower(word[1]) % ('a' - 1);
    if(a==39)
   {a=27;}}
   else
   {a=0;}

   if(st>2)
   { s = tolower(word[2]) % ('a' - 1);
   if(s==39)
   {s=27;}}
   else
   {s=0;}



    return h;
    return a;
    return s;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < (N - 2) * N * N  ; i++)
    {
        hashtable[i % (N - 2)][(i / (N - 2) ) % N][(i /((N - 2) * N ))% N]= NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];


    // Insert words into hash table
    while (fscanf(file, "%s", word)!= EOF)
    {
      hash(word);
      node * w = malloc(sizeof(node));
      if(!w)
      {
          return 1;
      }
      strcpy(w->word,word);
      w->next = NULL;

      if (hashtable[h][a][s])
     {
         w->next = hashtable[h][a][s];
     }


      hashtable[h][a][s]=w;
    n++;
    }


    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return n;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int sl = strlen(word);
    char wd[LENGTH + 1];
    for(int t = 0; t < sl; t++)
   {
        wd[t] = tolower(word[t]);
        wd[t + 1] = '\0';
   }

    hash(word);
    node * ot = hashtable[h][a][s];
    while ( ot != NULL)
   {
        int x = strcmp(wd, ot->word);
        if (x == 0)
        {
            return true;
            break;
        }
        ot= ot->next;
    }
    return false;

}



// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{   for (int i = 0; i <(N - 2) * N * N ; i++)
    {
       node *ot = hashtable[i % (N - 2)][(i / (N - 2) ) % N][(i /((N - 2) * N ))% N];
    struct node * next;
    while (ot != NULL)
    {
        next = ot->next;
        free(ot);
        ot = next;
    }

    }
    // TOD
    return true;
}
