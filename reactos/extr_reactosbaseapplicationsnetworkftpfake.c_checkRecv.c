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
struct timeval {int tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stderr ; 

int checkRecv(SOCKET s)
{
   int testVal;
   fd_set sSet;
   struct timeval timeout;
   timeout.tv_sec = 60;

   FD_ZERO(&sSet);

   FD_SET(s, &sSet);

   testVal = select(0, &sSet, NULL, NULL, &timeout);

   if (testVal == SOCKET_ERROR)
      fprintf(stderr, "Socket Error");

   return testVal;
}