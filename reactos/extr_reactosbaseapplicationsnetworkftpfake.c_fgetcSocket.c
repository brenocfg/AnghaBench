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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EOF ; 
 int ERROR ; 
 int SOCKET_ERROR ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 

int fgetcSocket(int s)
{
   static int index = 0;
   static int total = 0;
   static char buffer[4096];

   if (index == total)
     {
       index = 0;
       total = recv(s, buffer, sizeof(buffer), 0);

       if (total == SOCKET_ERROR)
     {
       total = 0;
       return ERROR;
     }

       if (total == 0)
     return EOF;
     }
   return buffer[index++];
}