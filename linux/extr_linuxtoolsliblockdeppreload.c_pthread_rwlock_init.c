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
typedef  int /*<<< orphan*/  pthread_rwlockattr_t ;
typedef  int /*<<< orphan*/  pthread_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_lock (int /*<<< orphan*/ *) ; 
 int ll_pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  try_init_preload () ; 

int pthread_rwlock_init(pthread_rwlock_t *rwlock,
			const pthread_rwlockattr_t *attr)
{
	int r;

	try_init_preload();

	r = ll_pthread_rwlock_init(rwlock, attr);
	if (r == 0)
		__get_lock(rwlock);

	return r;
}