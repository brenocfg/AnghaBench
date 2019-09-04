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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_ROBUST ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  inheritor ; 
 int lockCount ; 
 int /*<<< orphan*/ * mutex ; 
 int /*<<< orphan*/  owner ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_setrobust (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main()
{
  pthread_t to, ti;
  pthread_mutexattr_t ma;
  int order[3];

  assert(pthread_mutexattr_init(&ma) == 0);
  assert(pthread_mutexattr_setrobust(&ma, PTHREAD_MUTEX_ROBUST) == 0);

  order[0]=0;
  order[1]=1;
  order[2]=2;
  lockCount = 0;
  assert(pthread_mutex_init(&mutex[0], &ma) == 0);
  assert(pthread_mutex_init(&mutex[1], &ma) == 0);
  assert(pthread_mutex_init(&mutex[2], &ma) == 0);
  assert(pthread_create(&to, NULL, owner, NULL) == 0);
  Sleep(100);
  assert(pthread_create(&ti, NULL, inheritor, (void *)order) == 0);
  assert(pthread_join(to, NULL) == 0);
  assert(pthread_join(ti, NULL) == 0);
  assert(lockCount == 6);
  assert(pthread_mutex_lock(&mutex[0]) == 0);
  assert(pthread_mutex_unlock(&mutex[0]) == 0);
  assert(pthread_mutex_destroy(&mutex[0]) == 0);
  assert(pthread_mutex_lock(&mutex[1]) == 0);
  assert(pthread_mutex_unlock(&mutex[1]) == 0);
  assert(pthread_mutex_destroy(&mutex[1]) == 0);
  assert(pthread_mutex_lock(&mutex[2]) == 0);
  assert(pthread_mutex_unlock(&mutex[2]) == 0);
  assert(pthread_mutex_destroy(&mutex[2]) == 0);

  order[0]=1;
  order[1]=0;
  order[2]=2;
  lockCount = 0;
  assert(pthread_mutex_init(&mutex[0], &ma) == 0);
  assert(pthread_mutex_init(&mutex[1], &ma) == 0);
  assert(pthread_mutex_init(&mutex[2], &ma) == 0);
  assert(pthread_create(&to, NULL, owner, NULL) == 0);
  Sleep(100);
  assert(pthread_create(&ti, NULL, inheritor, (void *)order) == 0);
  assert(pthread_join(to, NULL) == 0);
  assert(pthread_join(ti, NULL) == 0);
  assert(lockCount == 6);
  assert(pthread_mutex_lock(&mutex[0]) == 0);
  assert(pthread_mutex_unlock(&mutex[0]) == 0);
  assert(pthread_mutex_destroy(&mutex[0]) == 0);
  assert(pthread_mutex_lock(&mutex[1]) == 0);
  assert(pthread_mutex_unlock(&mutex[1]) == 0);
  assert(pthread_mutex_destroy(&mutex[1]) == 0);
  assert(pthread_mutex_lock(&mutex[2]) == 0);
  assert(pthread_mutex_unlock(&mutex[2]) == 0);
  assert(pthread_mutex_destroy(&mutex[2]) == 0);

  order[0]=0;
  order[1]=2;
  order[2]=1;
  lockCount = 0;
  assert(pthread_mutex_init(&mutex[0], &ma) == 0);
  assert(pthread_mutex_init(&mutex[1], &ma) == 0);
  assert(pthread_mutex_init(&mutex[2], &ma) == 0);
  assert(pthread_create(&to, NULL, owner, NULL) == 0);
  Sleep(100);
  assert(pthread_create(&ti, NULL, inheritor, (void *)order) == 0);
  assert(pthread_join(to, NULL) == 0);
  assert(pthread_join(ti, NULL) == 0);
  assert(lockCount == 6);
  assert(pthread_mutex_lock(&mutex[0]) == 0);
  assert(pthread_mutex_unlock(&mutex[0]) == 0);
  assert(pthread_mutex_destroy(&mutex[0]) == 0);
  assert(pthread_mutex_lock(&mutex[1]) == 0);
  assert(pthread_mutex_unlock(&mutex[1]) == 0);
  assert(pthread_mutex_destroy(&mutex[1]) == 0);
  assert(pthread_mutex_lock(&mutex[2]) == 0);
  assert(pthread_mutex_unlock(&mutex[2]) == 0);
  assert(pthread_mutex_destroy(&mutex[2]) == 0);

  order[0]=2;
  order[1]=1;
  order[2]=0;
  lockCount = 0;
  assert(pthread_mutex_init(&mutex[0], &ma) == 0);
  assert(pthread_mutex_init(&mutex[1], &ma) == 0);
  assert(pthread_mutex_init(&mutex[2], &ma) == 0);
  assert(pthread_create(&to, NULL, owner, NULL) == 0);
  Sleep(100);
  assert(pthread_create(&ti, NULL, inheritor, (void *)order) == 0);
  assert(pthread_join(to, NULL) == 0);
  assert(pthread_join(ti, NULL) == 0);
  assert(lockCount == 6);
  assert(pthread_mutex_lock(&mutex[0]) == 0);
  assert(pthread_mutex_unlock(&mutex[0]) == 0);
  assert(pthread_mutex_destroy(&mutex[0]) == 0);
  assert(pthread_mutex_lock(&mutex[1]) == 0);
  assert(pthread_mutex_unlock(&mutex[1]) == 0);
  assert(pthread_mutex_destroy(&mutex[1]) == 0);
  assert(pthread_mutex_lock(&mutex[2]) == 0);
  assert(pthread_mutex_unlock(&mutex[2]) == 0);
  assert(pthread_mutex_destroy(&mutex[2]) == 0);

  assert(pthread_mutexattr_destroy(&ma) == 0);

  return 0;
}