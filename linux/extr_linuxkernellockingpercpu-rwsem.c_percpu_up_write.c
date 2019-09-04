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
struct percpu_rw_semaphore {int /*<<< orphan*/  rss; int /*<<< orphan*/  rw_sem; int /*<<< orphan*/  readers_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_sync_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void percpu_up_write(struct percpu_rw_semaphore *sem)
{
	/*
	 * Signal the writer is done, no fast path yet.
	 *
	 * One reason that we cannot just immediately flip to readers_fast is
	 * that new readers might fail to see the results of this writer's
	 * critical section.
	 *
	 * Therefore we force it through the slow path which guarantees an
	 * acquire and thereby guarantees the critical section's consistency.
	 */
	smp_store_release(&sem->readers_block, 0);

	/*
	 * Release the write lock, this will allow readers back in the game.
	 */
	up_write(&sem->rw_sem);

	/*
	 * Once this completes (at least one RCU-sched grace period hence) the
	 * reader fast path will be available again. Safe to use outside the
	 * exclusive write lock because its counting.
	 */
	rcu_sync_exit(&sem->rss);
}