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
struct worker_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  worklist; int /*<<< orphan*/  nr_running; } ;
struct worker {int flags; int sleeping; int /*<<< orphan*/  task; struct worker_pool* pool; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WORKER_NOT_RUNNING ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct worker* first_idle_worker (struct worker_pool*) ; 
 struct worker* kthread_data (struct task_struct*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void wq_worker_sleeping(struct task_struct *task)
{
	struct worker *next, *worker = kthread_data(task);
	struct worker_pool *pool;

	/*
	 * Rescuers, which may not have all the fields set up like normal
	 * workers, also reach here, let's not access anything before
	 * checking NOT_RUNNING.
	 */
	if (worker->flags & WORKER_NOT_RUNNING)
		return;

	pool = worker->pool;

	if (WARN_ON_ONCE(worker->sleeping))
		return;

	worker->sleeping = 1;
	spin_lock_irq(&pool->lock);

	/*
	 * The counterpart of the following dec_and_test, implied mb,
	 * worklist not empty test sequence is in insert_work().
	 * Please read comment there.
	 *
	 * NOT_RUNNING is clear.  This means that we're bound to and
	 * running on the local cpu w/ rq lock held and preemption
	 * disabled, which in turn means that none else could be
	 * manipulating idle_list, so dereferencing idle_list without pool
	 * lock is safe.
	 */
	if (atomic_dec_and_test(&pool->nr_running) &&
	    !list_empty(&pool->worklist)) {
		next = first_idle_worker(pool);
		if (next)
			wake_up_process(next->task);
	}
	spin_unlock_irq(&pool->lock);
}