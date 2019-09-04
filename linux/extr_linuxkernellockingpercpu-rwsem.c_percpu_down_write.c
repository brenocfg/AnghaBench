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
struct percpu_rw_semaphore {int /*<<< orphan*/  writer; int /*<<< orphan*/  readers_block; int /*<<< orphan*/  rw_sem; int /*<<< orphan*/  rss; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_sync_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcuwait_wait_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readers_active_check (struct percpu_rw_semaphore*) ; 
 int /*<<< orphan*/  smp_mb () ; 

void percpu_down_write(struct percpu_rw_semaphore *sem)
{
	/* Notify readers to take the slow path. */
	rcu_sync_enter(&sem->rss);

	down_write(&sem->rw_sem);

	/*
	 * Notify new readers to block; up until now, and thus throughout the
	 * longish rcu_sync_enter() above, new readers could still come in.
	 */
	WRITE_ONCE(sem->readers_block, 1);

	smp_mb(); /* D matches A */

	/*
	 * If they don't see our writer of readers_block, then we are
	 * guaranteed to see their sem->read_count increment, and therefore
	 * will wait for them.
	 */

	/* Wait for all now active readers to complete. */
	rcuwait_wait_event(&sem->writer, readers_active_check(sem));
}