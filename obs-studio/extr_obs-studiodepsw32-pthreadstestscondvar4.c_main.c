#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timespec {long tv_sec; int tv_nsec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;
struct TYPE_10__ {scalar_t__ shared; int /*<<< orphan*/ * notbusy; int /*<<< orphan*/ * lock; } ;
struct TYPE_9__ {int const millitm; scalar_t__ time; } ;
typedef  TYPE_2__ PTW32_STRUCT_TIMEB ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 int NUMTHREADS ; 
 int /*<<< orphan*/ * PTHREAD_COND_INITIALIZER ; 
 int /*<<< orphan*/ * PTHREAD_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__ cvthing ; 
 int /*<<< orphan*/  mythread ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ **,int /*<<< orphan*/ **,struct timespec*) ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (TYPE_1__,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ **) ; 
 TYPE_1__ pthread_self () ; 

int
main()
{
  pthread_t t[NUMTHREADS];
  struct timespec abstime = { 0, 0 };
  PTW32_STRUCT_TIMEB currSysTime;
  const DWORD NANOSEC_PER_MILLISEC = 1000000;

  cvthing.shared = 0;

  assert((t[0] = pthread_self()).p != NULL);

  assert(cvthing.notbusy == PTHREAD_COND_INITIALIZER);

  assert(cvthing.lock == PTHREAD_MUTEX_INITIALIZER);

  assert(pthread_mutex_lock(&cvthing.lock) == 0);

  assert(cvthing.lock != PTHREAD_MUTEX_INITIALIZER);

  /* get current system time */
  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = (long)currSysTime.time;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  abstime.tv_sec += 5;

  assert(pthread_cond_timedwait(&cvthing.notbusy, &cvthing.lock, &abstime) == ETIMEDOUT);
  
  assert(cvthing.notbusy != PTHREAD_COND_INITIALIZER);

  assert(pthread_create(&t[1], NULL, mythread, (void *) 1) == 0);

  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = (long)currSysTime.time;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  abstime.tv_sec += 5;

  while (! (cvthing.shared > 0))
    assert(pthread_cond_timedwait(&cvthing.notbusy, &cvthing.lock, &abstime) == 0);

  assert(cvthing.shared > 0);

  assert(pthread_mutex_unlock(&cvthing.lock) == 0);

  assert(pthread_join(t[1], NULL) == 0);

  assert(pthread_mutex_destroy(&cvthing.lock) == 0);

  assert(cvthing.lock == NULL);

  assert(pthread_cond_destroy(&cvthing.notbusy) == 0);

  assert(cvthing.notbusy == NULL);

  return 0;
}