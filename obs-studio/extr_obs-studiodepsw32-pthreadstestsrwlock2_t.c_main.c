#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {long tv_sec; int tv_nsec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int const millitm; scalar_t__ time; } ;
typedef  TYPE_1__ PTW32_STRUCT_TIMEB ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * PTHREAD_RWLOCK_INITIALIZER ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_rwlock_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_rwlock_timedrdlock (int /*<<< orphan*/ **,struct timespec*) ; 
 scalar_t__ pthread_rwlock_unlock (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * rwlock ; 

int
main()
{
  struct timespec abstime = { 0, 0 };
  PTW32_STRUCT_TIMEB currSysTime;
  const DWORD NANOSEC_PER_MILLISEC = 1000000;

  PTW32_FTIME(&currSysTime);

  abstime.tv_sec = (long)currSysTime.time;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;

  abstime.tv_sec += 1;

  assert(rwlock == PTHREAD_RWLOCK_INITIALIZER);

  assert(pthread_rwlock_timedrdlock(&rwlock, &abstime) == 0);

  assert(rwlock != PTHREAD_RWLOCK_INITIALIZER);

  assert(rwlock != NULL);

  assert(pthread_rwlock_unlock(&rwlock) == 0);

  assert(pthread_rwlock_destroy(&rwlock) == 0);

  assert(rwlock == NULL);

  return 0;
}