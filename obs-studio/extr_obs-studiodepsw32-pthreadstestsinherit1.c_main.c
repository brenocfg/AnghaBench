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
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ GetThreadPriority (int /*<<< orphan*/ ) ; 
 int PTHREAD_INHERIT_SCHED ; 
 int PTW32TEST_MAXPRIORITIES ; 
 int /*<<< orphan*/  PTW32TEST_THREAD_INIT_PRIO ; 
 int SCHED_OTHER ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  getValidPriorities ; 
 int maxPrio ; 
 int minPrio ; 
 scalar_t__ pthread_attr_getinheritsched (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setinheritsched (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_getschedparam (int /*<<< orphan*/ ,int*,struct sched_param*) ; 
 int /*<<< orphan*/  pthread_getw32threadhandle_np (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ pthread_setschedparam (int /*<<< orphan*/ ,int,struct sched_param*) ; 
 int sched_get_priority_max (int) ; 
 int sched_get_priority_min (int) ; 
 scalar_t__* validPriorities ; 

int
main()
{
  pthread_t t;
  pthread_t mainThread = pthread_self();
  pthread_attr_t attr;
  void * result = NULL;
  struct sched_param param;
  struct sched_param mainParam;
  int prio;
  int policy;
  int inheritsched = -1;
  pthread_t threadID = pthread_self();
  HANDLE threadH = pthread_getw32threadhandle_np(threadID);

  assert((maxPrio = sched_get_priority_max(SCHED_OTHER)) != -1);
  assert((minPrio = sched_get_priority_min(SCHED_OTHER)) != -1);

  assert(pthread_create(&t, NULL, getValidPriorities, NULL) == 0);
  assert(pthread_join(t, &result) == 0);

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED) == 0);
  assert(pthread_attr_getinheritsched(&attr, &inheritsched) == 0);
  assert(inheritsched == PTHREAD_INHERIT_SCHED);

  for (prio = minPrio; prio <= maxPrio; prio++)
    {
      mainParam.sched_priority = prio;

      /* Set the thread's priority to a known initial value. */
      SetThreadPriority(threadH, PTW32TEST_THREAD_INIT_PRIO);

      /* Change the main thread priority */
      assert(pthread_setschedparam(mainThread, SCHED_OTHER, &mainParam) == 0);
      assert(pthread_getschedparam(mainThread, &policy, &mainParam) == 0);
      assert(policy == SCHED_OTHER);
      /* Priority returned below should be the level set by pthread_setschedparam(). */
      assert(mainParam.sched_priority == prio);
      assert(GetThreadPriority(threadH) ==
               validPriorities[prio+(PTW32TEST_MAXPRIORITIES/2)]);

      for (param.sched_priority = prio;
           param.sched_priority <= maxPrio;
           param.sched_priority++)
        {
          /* The new thread create should ignore this new priority */
          assert(pthread_attr_setschedparam(&attr, &param) == 0);
          assert(pthread_create(&t, &attr, func, NULL) == 0);
          pthread_join(t, &result);
          assert((int)(size_t) result == mainParam.sched_priority);
        }
    }

  return 0;
}