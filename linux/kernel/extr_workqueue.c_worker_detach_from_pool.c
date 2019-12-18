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
struct worker_pool {struct completion* detach_completion; int /*<<< orphan*/  workers; } ;
struct worker {int flags; struct worker_pool* pool; int /*<<< orphan*/  node; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int WORKER_REBOUND ; 
 int WORKER_UNBOUND ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_pool_attach_mutex ; 

__attribute__((used)) static void worker_detach_from_pool(struct worker *worker)
{
	struct worker_pool *pool = worker->pool;
	struct completion *detach_completion = NULL;

	mutex_lock(&wq_pool_attach_mutex);

	list_del(&worker->node);
	worker->pool = NULL;

	if (list_empty(&pool->workers))
		detach_completion = pool->detach_completion;
	mutex_unlock(&wq_pool_attach_mutex);

	/* clear leftover flags without pool->lock after it is detached */
	worker->flags &= ~(WORKER_UNBOUND | WORKER_REBOUND);

	if (detach_completion)
		complete(detach_completion);
}