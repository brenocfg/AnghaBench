#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int MAX_ASCII ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  checkRecv (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 

char *fgetsSocket(int s, char *string)
{
   char buffer[2] = {0};
   int i, count;

   for (i = 0, count = 1; count != 0 && buffer[0] != '\n'; i++)
   {
      checkRecv(s);

      count = recv(s, buffer, 1, 0);

      if (count == SOCKET_ERROR)
      {
     printf("Error in fgetssocket");
     return NULL;
      }

      if (count == 1)
      {
     string[i] = buffer[0];

     if (i == MAX_ASCII - 3)
     {
        count = 0;
        string[++i] = '\n';
        string[++i] = '\0';
     }
      }
      else
      {
     if (i == 0)
        return NULL;
     else
     {
        string[i] = '\n';
        string[i + 1] = '\0'; // This is risky
        return string;
     }

      }

   }
   string[i] = '\0';

#ifdef DEBUG_IN
   printf("%s", string);
#endif
   return string;
}