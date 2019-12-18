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
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PTW32_FTIME (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cnd ; 
 int /*<<< orphan*/  mtx ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int main()
{
   int rc;

   struct timespec abstime = { 0, 0 };
   PTW32_STRUCT_TIMEB currSysTime;
   const DWORD NANOSEC_PER_MILLISEC = 1000000;

   assert(pthread_cond_init(&cnd, 0) == 0);
   assert(pthread_mutex_init(&mtx, 0) == 0);

   /* get current system time */
   PTW32_FTIME(&currSysTime);

   abstime.tv_sec = (long)currSysTime.time;
   abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;
   abstime.tv_sec += 1;

   /* Here pthread_cond_timedwait should time out after one second. */

   assert(pthread_mutex_lock(&mtx) == 0);

   assert((rc = pthread_cond_timedwait(&cnd, &mtx, &abstime)) == ETIMEDOUT);

   assert(pthread_mutex_unlock(&mtx) == 0);

   /* Here, the condition variable is signaled, but there are no
      threads waiting on it. The signal should be lost and
      the next pthread_cond_timedwait should time out too. */

//   assert(pthread_mutex_lock(&mtx) == 0);

   assert((rc = pthread_cond_signal(&cnd)) == 0);

//   assert(pthread_mutex_unlock(&mtx) == 0);

   assert(pthread_mutex_lock(&mtx) == 0);

   abstime.tv_sec = (long)currSysTime.time;
   abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.millitm;
   abstime.tv_sec += 1;

   assert((rc = pthread_cond_timedwait(&cnd, &mtx, &abstime)) == ETIMEDOUT);

   assert(pthread_mutex_unlock(&mtx) == 0);

   return 0;
}