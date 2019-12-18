#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_3__ {int myPrio; int threadnum; size_t oncenum; int /*<<< orphan*/  w32Thread; } ;
typedef  TYPE_1__ bag_t ;
struct TYPE_4__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mycleanupfunc ; 
 int /*<<< orphan*/  myinitfunc ; 
 TYPE_2__ numThreads ; 
 int /*<<< orphan*/ * once ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_getw32threadhandle_np (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setschedparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 

void *
mythread(void * arg)
{
  bag_t * bag = (bag_t *) arg;
  struct sched_param param;

  /*
   * Cancel every thread. These threads are deferred cancelable only, so
   * only the thread performing the init_routine will see it (there are
   * no other cancelation points here). The result will be that every thread
   * eventually cancels only when it becomes the new initter.
   */
  pthread_t self = pthread_self();
  bag->w32Thread = pthread_getw32threadhandle_np(self);
  /*
   * Set priority between -2 and 2 inclusive.
   */
  bag->myPrio = (bag->threadnum % 5) - 2;
  param.sched_priority = bag->myPrio;
  pthread_setschedparam(self, SCHED_OTHER, &param);

  /* Trigger a cancellation at the next cancellation point in this thread */
  pthread_cancel(self);
#if 0
  pthread_cleanup_push(mycleanupfunc, arg);
  assert(pthread_once(&once[bag->oncenum], myinitfunc) == 0);
  pthread_cleanup_pop(1);
#else
  assert(pthread_once(&once[bag->oncenum], myinitfunc) == 0);
#endif
  EnterCriticalSection(&numThreads.cs);
  numThreads.i++;
  LeaveCriticalSection(&numThreads.cs);
  return 0;
}