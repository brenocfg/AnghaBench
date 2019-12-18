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
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetThreadPriority (int /*<<< orphan*/ ) ; 
 int PTW32TEST_MAXPRIORITIES ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  assert (int) ; 
 int maxPrio ; 
 int minPrio ; 
 int /*<<< orphan*/  pthread_getw32threadhandle_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ pthread_setschedparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/ * validPriorities ; 

void *
getValidPriorities(void * arg)
{
  int prioSet;
  pthread_t thread = pthread_self();
  HANDLE threadH = pthread_getw32threadhandle_np(thread);
  struct sched_param param;

  for (prioSet = minPrio;
       prioSet <= maxPrio;
       prioSet++)
    {
        /*
       * If prioSet is invalid then the threads priority is unchanged
       * from the previous value. Make the previous value a known
       * one so that we can check later.
       */
        param.sched_priority = prioSet;
        assert(pthread_setschedparam(thread, SCHED_OTHER, &param) == 0);
        validPriorities[prioSet+(PTW32TEST_MAXPRIORITIES/2)] = GetThreadPriority(threadH);
    }

  return (void *) 0;
}