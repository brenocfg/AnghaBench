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
struct worker_pool {scalar_t__ nr_idle; int flags; scalar_t__ nr_workers; int /*<<< orphan*/  nr_running; int /*<<< orphan*/  idle_timer; int /*<<< orphan*/  idle_list; } ;
struct TYPE_2__ {scalar_t__ pprev; scalar_t__ next; } ;
struct worker {int flags; int /*<<< orphan*/  entry; scalar_t__ last_active; TYPE_1__ hentry; struct worker_pool* pool; } ;

/* Variables and functions */
 scalar_t__ IDLE_WORKER_TIMEOUT ; 
 int POOL_DISASSOCIATED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int WORKER_IDLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ too_many_workers (struct worker_pool*) ; 

__attribute__((used)) static void worker_enter_idle(struct worker *worker)
{
	struct worker_pool *pool = worker->pool;

	if (WARN_ON_ONCE(worker->flags & WORKER_IDLE) ||
	    WARN_ON_ONCE(!list_empty(&worker->entry) &&
			 (worker->hentry.next || worker->hentry.pprev)))
		return;

	/* can't use worker_set_flags(), also called from create_worker() */
	worker->flags |= WORKER_IDLE;
	pool->nr_idle++;
	worker->last_active = jiffies;

	/* idle_list is LIFO */
	list_add(&worker->entry, &pool->idle_list);

	if (too_many_workers(pool) && !timer_pending(&pool->idle_timer))
		mod_timer(&pool->idle_timer, jiffies + IDLE_WORKER_TIMEOUT);

	/*
	 * Sanity check nr_running.  Because unbind_workers() releases
	 * pool->lock between setting %WORKER_UNBOUND and zapping
	 * nr_running, the warning may trigger spuriously.  Check iff
	 * unbind is not in progress.
	 */
	WARN_ON_ONCE(!(pool->flags & POOL_DISASSOCIATED) &&
		     pool->nr_workers == pool->nr_idle &&
		     atomic_read(&pool->nr_running));
}