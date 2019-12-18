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
 scalar_t__ SOCKET_ERROR ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int fputcSocket(int s, char putChar)
{
   char buffer[2];

   buffer[0] = putChar;
   buffer[1] = '\0';

   if(SOCKET_ERROR==send(s, buffer, 1, 0)) {
       int iret=WSAGetLastError ();
       fprintf(stdout,"fputcSocket: %d\n",iret);
       return 0;
   }
   else {
    return putChar;
   }
}