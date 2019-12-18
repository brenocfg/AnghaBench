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
typedef  int /*<<< orphan*/  pthread_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __del_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (int /*<<< orphan*/ *,int) ; 
 int ll_pthread_rwlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_init_preload () ; 

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
	try_init_preload();

	debug_check_no_locks_freed(rwlock, sizeof(*rwlock));
	__del_lock(__get_lock(rwlock));
	return ll_pthread_rwlock_destroy(rwlock);
}