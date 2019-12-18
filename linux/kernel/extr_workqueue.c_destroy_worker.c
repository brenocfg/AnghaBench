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
struct worker_pool {int /*<<< orphan*/  nr_idle; int /*<<< orphan*/  nr_workers; int /*<<< orphan*/  lock; } ;
struct worker {int current_work; int flags; int /*<<< orphan*/  task; int /*<<< orphan*/  entry; int /*<<< orphan*/  scheduled; struct worker_pool* pool; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int WORKER_DIE ; 
 int WORKER_IDLE ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_worker(struct worker *worker)
{
	struct worker_pool *pool = worker->pool;

	lockdep_assert_held(&pool->lock);

	/* sanity check frenzy */
	if (WARN_ON(worker->current_work) ||
	    WARN_ON(!list_empty(&worker->scheduled)) ||
	    WARN_ON(!(worker->flags & WORKER_IDLE)))
		return;

	pool->nr_workers--;
	pool->nr_idle--;

	list_del_init(&worker->entry);
	worker->flags |= WORKER_DIE;
	wake_up_process(worker->task);
}