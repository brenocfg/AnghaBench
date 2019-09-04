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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  __del_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (int /*<<< orphan*/ *,int) ; 
 int ll_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_init_preload () ; 

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	try_init_preload();

	/*
	 * Let's see if we're releasing a lock that's held.
	 *
	 * TODO: Hook into free() and add that check there as well.
	 */
	debug_check_no_locks_freed(mutex, sizeof(*mutex));
	__del_lock(__get_lock(mutex));
	return ll_pthread_mutex_destroy(mutex);
}