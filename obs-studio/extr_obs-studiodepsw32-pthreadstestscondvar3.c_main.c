#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timespec {long tv_sec; int tv_nsec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;
struct TYPE_8__ {int const millitm; scalar_t__ time; } ;
typedef  TYPE_2__ PTW32_STRUCT_TIMEB ;
typedef  int DWORD ;

/* Variables and functions */
 int NUMTHREADS ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cv ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (TYPE_1__,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ pthread_self () ; 
 scalar_t__ shared ; 

int
main()
{
  pthread_t t[NUMTHREADS];
  struct timespec abstime = { 0, 0 };
  PTW32_STRUCT_TIMEB currSysTime;
  const DWORD NANOSEC_PER_MILLISEC = 1000000;

  assert((t[0] = pthread_self()).p != NULL);

  assert(pthread_cond_init(&cv, NULL) == 0);

  assert(pthread_mutex_init(&mutex, NULL) == 0);

  assert(pthread_mutex_lock(&mutex) == 0);

  /* get current system time */
  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = (long)currSysTime.time;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  assert(pthread_create(&t[1], NULL, mythread, (void *) 1) == 0);

  abstime.tv_sec += 5;

  while (! (shared > 0))
    assert(pthread_cond_timedwait(&cv, &mutex, &abstime) == 0);

  assert(shared > 0);

  assert(pthread_mutex_unlock(&mutex) == 0);

  assert(pthread_join(t[1], NULL) == 0);

  assert(pthread_cond_destroy(&cv) == 0);

  return 0;
}