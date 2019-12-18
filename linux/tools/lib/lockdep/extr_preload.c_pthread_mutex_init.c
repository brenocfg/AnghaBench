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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_lock (int /*<<< orphan*/ *) ; 
 int ll_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  try_init_preload () ; 

int pthread_mutex_init(pthread_mutex_t *mutex,
			const pthread_mutexattr_t *attr)
{
	int r;

	/*
	 * We keep trying to init our preload module because there might be
	 * code in init sections that tries to touch locks before we are
	 * initialized, in that case we'll need to manually call preload
	 * to get us going.
	 *
	 * Funny enough, kernel's lockdep had the same issue, and used
	 * (almost) the same solution. See look_up_lock_class() in
	 * kernel/locking/lockdep.c for details.
	 */
	try_init_preload();

	r = ll_pthread_mutex_init(mutex, attr);
	if (r == 0)
		/*
		 * We do a dummy initialization here so that lockdep could
		 * warn us if something fishy is going on - such as
		 * initializing a held lock.
		 */
		__get_lock(mutex);

	return r;
}