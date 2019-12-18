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

/* Variables and functions */
 int GetThreadPriority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTHREAD_EXPLICIT_SCHED ; 
 int PTW32TEST_MAXPRIORITIES ; 
 int /*<<< orphan*/  PTW32TEST_THREAD_INIT_PRIO ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  getValidPriorities ; 
 int maxPrio ; 
 int minPrio ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setinheritsched (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_getw32threadhandle_np (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int sched_get_priority_min (int /*<<< orphan*/ ) ; 
 int* validPriorities ; 

int
main()
{
  pthread_t t;
  pthread_attr_t attr;
  void * result = NULL;
  struct sched_param param;

  assert((maxPrio = sched_get_priority_max(SCHED_OTHER)) != -1);
  assert((minPrio = sched_get_priority_min(SCHED_OTHER)) != -1);

  assert(pthread_create(&t, NULL, getValidPriorities, NULL) == 0);
  assert(pthread_join(t, &result) == 0);

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) == 0);

  /* Set the thread's priority to a known initial value. */
  SetThreadPriority(pthread_getw32threadhandle_np(pthread_self()),
                    PTW32TEST_THREAD_INIT_PRIO);

  printf("Using pthread_getschedparam\n");
  printf("%10s %10s %10s\n", "Set value", "Get value", "Win priority");

  for (param.sched_priority = minPrio;
       param.sched_priority <= maxPrio;
       param.sched_priority++)
    {
      int prio;

      assert(pthread_attr_setschedparam(&attr, &param) == 0);
      assert(pthread_create(&t, &attr, func, (void *) &attr) == 0);

      assert((prio = GetThreadPriority(pthread_getw32threadhandle_np(t)))
             == validPriorities[param.sched_priority+(PTW32TEST_MAXPRIORITIES/2)]);

      assert(pthread_join(t, &result) == 0);

      assert(param.sched_priority == (int)(size_t) result);
      printf("%10d %10d %10d\n", param.sched_priority, (int)(size_t) result, prio);
    }

  return 0;
}