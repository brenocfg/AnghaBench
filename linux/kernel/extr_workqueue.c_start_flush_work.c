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
struct wq_barrier {int dummy; } ;
struct worker_pool {int /*<<< orphan*/  lock; } ;
struct worker {struct pool_workqueue* current_pwq; } ;
struct work_struct {int dummy; } ;
struct pool_workqueue {TYPE_1__* wq; struct worker_pool* pool; } ;
struct TYPE_2__ {int saved_max_active; int /*<<< orphan*/  lockdep_map; scalar_t__ rescuer; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_flush_dependency (TYPE_1__*,struct work_struct*) ; 
 struct worker* find_worker_executing_work (struct worker_pool*,struct work_struct*) ; 
 struct worker_pool* get_work_pool (struct work_struct*) ; 
 struct pool_workqueue* get_work_pwq (struct work_struct*) ; 
 int /*<<< orphan*/  insert_wq_barrier (struct pool_workqueue*,struct wq_barrier*,struct work_struct*,struct worker*) ; 
 int /*<<< orphan*/  lock_map_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool start_flush_work(struct work_struct *work, struct wq_barrier *barr,
			     bool from_cancel)
{
	struct worker *worker = NULL;
	struct worker_pool *pool;
	struct pool_workqueue *pwq;

	might_sleep();

	rcu_read_lock();
	pool = get_work_pool(work);
	if (!pool) {
		rcu_read_unlock();
		return false;
	}

	spin_lock_irq(&pool->lock);
	/* see the comment in try_to_grab_pending() with the same code */
	pwq = get_work_pwq(work);
	if (pwq) {
		if (unlikely(pwq->pool != pool))
			goto already_gone;
	} else {
		worker = find_worker_executing_work(pool, work);
		if (!worker)
			goto already_gone;
		pwq = worker->current_pwq;
	}

	check_flush_dependency(pwq->wq, work);

	insert_wq_barrier(pwq, barr, work, worker);
	spin_unlock_irq(&pool->lock);

	/*
	 * Force a lock recursion deadlock when using flush_work() inside a
	 * single-threaded or rescuer equipped workqueue.
	 *
	 * For single threaded workqueues the deadlock happens when the work
	 * is after the work issuing the flush_work(). For rescuer equipped
	 * workqueues the deadlock happens when the rescuer stalls, blocking
	 * forward progress.
	 */
	if (!from_cancel &&
	    (pwq->wq->saved_max_active == 1 || pwq->wq->rescuer)) {
		lock_map_acquire(&pwq->wq->lockdep_map);
		lock_map_release(&pwq->wq->lockdep_map);
	}
	rcu_read_unlock();
	return true;
already_gone:
	spin_unlock_irq(&pool->lock);
	rcu_read_unlock();
	return false;
}