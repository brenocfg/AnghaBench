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
struct rw_semaphore {int /*<<< orphan*/  count; int /*<<< orphan*/  wait_list; } ;

/* Variables and functions */
 long RWSEM_ACTIVE_WRITE_BIAS ; 
 long RWSEM_WAITING_BIAS ; 
 long atomic_long_cmpxchg_acquire (int /*<<< orphan*/ *,long,long) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwsem_set_owner (struct rw_semaphore*) ; 

__attribute__((used)) static inline bool rwsem_try_write_lock(long count, struct rw_semaphore *sem)
{
	/*
	 * Avoid trying to acquire write lock if count isn't RWSEM_WAITING_BIAS.
	 */
	if (count != RWSEM_WAITING_BIAS)
		return false;

	/*
	 * Acquire the lock by trying to set it to ACTIVE_WRITE_BIAS. If there
	 * are other tasks on the wait list, we need to add on WAITING_BIAS.
	 */
	count = list_is_singular(&sem->wait_list) ?
			RWSEM_ACTIVE_WRITE_BIAS :
			RWSEM_ACTIVE_WRITE_BIAS + RWSEM_WAITING_BIAS;

	if (atomic_long_cmpxchg_acquire(&sem->count, RWSEM_WAITING_BIAS, count)
							== RWSEM_WAITING_BIAS) {
		rwsem_set_owner(sem);
		return true;
	}

	return false;
}