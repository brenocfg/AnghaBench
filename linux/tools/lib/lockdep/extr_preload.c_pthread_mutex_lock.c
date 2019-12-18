#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_2__ {int /*<<< orphan*/  dep_map; } ;

/* Variables and functions */
 scalar_t__ _RET_IP_ ; 
 TYPE_1__* __get_lock (int /*<<< orphan*/ *) ; 
 int ll_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  try_init_preload () ; 

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	int r;

	try_init_preload();

	lock_acquire(&__get_lock(mutex)->dep_map, 0, 0, 0, 1, NULL,
			(unsigned long)_RET_IP_);
	/*
	 * Here's the thing with pthread mutexes: unlike the kernel variant,
	 * they can fail.
	 *
	 * This means that the behaviour here is a bit different from what's
	 * going on in the kernel: there we just tell lockdep that we took the
	 * lock before actually taking it, but here we must deal with the case
	 * that locking failed.
	 *
	 * To do that we'll "release" the lock if locking failed - this way
	 * we'll get lockdep doing the correct checks when we try to take
	 * the lock, and if that fails - we'll be back to the correct
	 * state by releasing it.
	 */
	r = ll_pthread_mutex_lock(mutex);
	if (r)
		lock_release(&__get_lock(mutex)->dep_map, 0, (unsigned long)_RET_IP_);

	return r;
}