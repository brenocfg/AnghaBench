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

/* Variables and functions */
 scalar_t__ GetThreadPriority (int /*<<< orphan*/ ) ; 
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int PTW32TEST_MAXPRIORITIES ; 
 int /*<<< orphan*/  PTW32TEST_THREAD_INIT_PRIO ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  endBarrier ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  getValidPriorities ; 
 int maxPrio ; 
 int minPrio ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_getw32threadhandle_np (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ pthread_setschedparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int sched_get_priority_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startBarrier ; 
 scalar_t__* validPriorities ; 

int
main()
{
  pthread_t t;
  void * result = NULL;
  int result2;
  struct sched_param param;

  assert((maxPrio = sched_get_priority_max(SCHED_OTHER)) != -1);
  assert((minPrio = sched_get_priority_min(SCHED_OTHER)) != -1);

  assert(pthread_create(&t, NULL, getValidPriorities, NULL) == 0);
  assert(pthread_join(t, &result) == 0);

  assert(pthread_barrier_init(&startBarrier, NULL, 2) == 0);
  assert(pthread_barrier_init(&endBarrier, NULL, 2) == 0);

  /* Set the thread's priority to a known initial value.
   * If the new priority is invalid then the threads priority
   * is unchanged from the previous value.
   */
  SetThreadPriority(pthread_getw32threadhandle_np(pthread_self()),
                    PTW32TEST_THREAD_INIT_PRIO);

  for (param.sched_priority = minPrio;
       param.sched_priority <= maxPrio;
       param.sched_priority++)
    {
      assert(pthread_create(&t, NULL, func, NULL) == 0);
      assert(pthread_setschedparam(t, SCHED_OTHER, &param) == 0);
      result2 = pthread_barrier_wait(&startBarrier);
      assert(result2 == 0 || result2 == PTHREAD_BARRIER_SERIAL_THREAD);
      result2 = pthread_barrier_wait(&endBarrier);
      assert(result2 == 0 || result2 == PTHREAD_BARRIER_SERIAL_THREAD);
      assert(GetThreadPriority(pthread_getw32threadhandle_np(t)) ==
	  validPriorities[param.sched_priority+(PTW32TEST_MAXPRIORITIES/2)]);
      pthread_join(t, &result);
      assert(param.sched_priority == (int)(size_t)result);
    }

  return 0;
}