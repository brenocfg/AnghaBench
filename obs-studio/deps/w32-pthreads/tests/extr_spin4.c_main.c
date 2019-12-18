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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  PTW32_STRUCT_TIMEB ;

/* Variables and functions */
 int GetDurationMilliSecs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTW32_FTIME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  currSysTimeStart ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int pthread_num_processors_np () ; 
 scalar_t__ pthread_spin_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_yield () ; 
 int washere ; 

int
main()
{
  void* result = (void*)0;
  pthread_t t;
  int CPUs;
  PTW32_STRUCT_TIMEB sysTime;

  if ((CPUs = pthread_num_processors_np()) == 1)
    {
      printf("Test not run - it requires multiple CPUs.\n");
	exit(0);
    }

  assert(pthread_spin_lock(&lock) == 0);

  assert(pthread_create(&t, NULL, func, NULL) == 0);

  while (washere == 0)
    {
      sched_yield();
    }

  do
    {
      sched_yield();
      PTW32_FTIME(&sysTime);
    }
  while (GetDurationMilliSecs(currSysTimeStart, sysTime) <= 1000);

  assert(pthread_spin_unlock(&lock) == 0);

  assert(pthread_join(t, &result) == 0);
  assert((int)(size_t)result > 1000);

  assert(pthread_spin_destroy(&lock) == 0);

  assert(washere == 1);

  return 0;
}