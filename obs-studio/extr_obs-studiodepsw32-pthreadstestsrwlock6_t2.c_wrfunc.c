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

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bankAccount ; 
 int pthread_rwlock_timedwrlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock1 ; 

void * wrfunc(void * arg)
{
  int result;

  result = pthread_rwlock_timedwrlock(&rwlock1, &abstime);
  if ((int) (size_t)arg == 1)
    {
      assert(result == 0);
      Sleep(2000);
      bankAccount += 10;
      assert(pthread_rwlock_unlock(&rwlock1) == 0);
      return ((void *)(size_t)bankAccount);
    }
  else if ((int) (size_t)arg == 2)
    {
      assert(result == ETIMEDOUT);
      return ((void *) 100);
    }

  return ((void *)(size_t)-1);
}