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
struct percpu_rw_semaphore {int /*<<< orphan*/  rw_sem; int /*<<< orphan*/ * read_count; int /*<<< orphan*/  readers_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  __down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __percpu_up_read (struct percpu_rw_semaphore*) ; 
 int /*<<< orphan*/  __up_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

int __percpu_down_read(struct percpu_rw_semaphore *sem, int try)
{
	/*
	 * Due to having preemption disabled the decrement happens on
	 * the same CPU as the increment, avoiding the
	 * increment-on-one-CPU-and-decrement-on-another problem.
	 *
	 * If the reader misses the writer's assignment of readers_block, then
	 * the writer is guaranteed to see the reader's increment.
	 *
	 * Conversely, any readers that increment their sem->read_count after
	 * the writer looks are guaranteed to see the readers_block value,
	 * which in turn means that they are guaranteed to immediately
	 * decrement their sem->read_count, so that it doesn't matter that the
	 * writer missed them.
	 */

	smp_mb(); /* A matches D */

	/*
	 * If !readers_block the critical section starts here, matched by the
	 * release in percpu_up_write().
	 */
	if (likely(!smp_load_acquire(&sem->readers_block)))
		return 1;

	/*
	 * Per the above comment; we still have preemption disabled and
	 * will thus decrement on the same CPU as we incremented.
	 */
	__percpu_up_read(sem);

	if (try)
		return 0;

	/*
	 * We either call schedule() in the wait, or we'll fall through
	 * and reschedule on the preempt_enable() in percpu_down_read().
	 */
	preempt_enable_no_resched();

	/*
	 * Avoid lockdep for the down/up_read() we already have them.
	 */
	__down_read(&sem->rw_sem);
	this_cpu_inc(*sem->read_count);
	__up_read(&sem->rw_sem);

	preempt_disable();
	return 1;
}