#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int oncenum; int threadnum; int myPrio; int /*<<< orphan*/  w32Thread; } ;
typedef  TYPE_1__ bag_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int GetThreadPriority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_lock ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

void
mycleanupfunc(void * arg)
{
  bag_t * bag = (bag_t *) arg;
  EnterCriticalSection(&print_lock);
  /*      once thrd  prio error */
  printf("%4d %4d %4d %4d\n",
	 bag->oncenum,
	 bag->threadnum,
	 bag->myPrio,
	 bag->myPrio - GetThreadPriority(bag->w32Thread));
  LeaveCriticalSection(&print_lock);
}