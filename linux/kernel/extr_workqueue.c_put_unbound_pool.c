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
struct worker_pool {scalar_t__ cpu; scalar_t__ id; int flags; int /*<<< orphan*/  rcu; int /*<<< orphan*/  mayday_timer; int /*<<< orphan*/  idle_timer; int /*<<< orphan*/ * detach_completion; int /*<<< orphan*/  workers; int /*<<< orphan*/  lock; scalar_t__ nr_idle; scalar_t__ nr_workers; int /*<<< orphan*/  hash_node; int /*<<< orphan*/  worklist; scalar_t__ refcnt; } ;
struct worker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int POOL_MANAGER_ACTIVE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_worker (struct worker*) ; 
 int /*<<< orphan*/  detach_completion ; 
 struct worker* first_idle_worker (struct worker_pool*) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_free_pool ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_pool_idr ; 
 int /*<<< orphan*/  wq_manager_wait ; 
 int /*<<< orphan*/  wq_pool_attach_mutex ; 
 int /*<<< orphan*/  wq_pool_mutex ; 

__attribute__((used)) static void put_unbound_pool(struct worker_pool *pool)
{
	DECLARE_COMPLETION_ONSTACK(detach_completion);
	struct worker *worker;

	lockdep_assert_held(&wq_pool_mutex);

	if (--pool->refcnt)
		return;

	/* sanity checks */
	if (WARN_ON(!(pool->cpu < 0)) ||
	    WARN_ON(!list_empty(&pool->worklist)))
		return;

	/* release id and unhash */
	if (pool->id >= 0)
		idr_remove(&worker_pool_idr, pool->id);
	hash_del(&pool->hash_node);

	/*
	 * Become the manager and destroy all workers.  This prevents
	 * @pool's workers from blocking on attach_mutex.  We're the last
	 * manager and @pool gets freed with the flag set.
	 */
	spin_lock_irq(&pool->lock);
	wait_event_lock_irq(wq_manager_wait,
			    !(pool->flags & POOL_MANAGER_ACTIVE), pool->lock);
	pool->flags |= POOL_MANAGER_ACTIVE;

	while ((worker = first_idle_worker(pool)))
		destroy_worker(worker);
	WARN_ON(pool->nr_workers || pool->nr_idle);
	spin_unlock_irq(&pool->lock);

	mutex_lock(&wq_pool_attach_mutex);
	if (!list_empty(&pool->workers))
		pool->detach_completion = &detach_completion;
	mutex_unlock(&wq_pool_attach_mutex);

	if (pool->detach_completion)
		wait_for_completion(pool->detach_completion);

	/* shut down the timers */
	del_timer_sync(&pool->idle_timer);
	del_timer_sync(&pool->mayday_timer);

	/* RCU protected to allow dereferences from get_work_pool() */
	call_rcu(&pool->rcu, rcu_free_pool);
}