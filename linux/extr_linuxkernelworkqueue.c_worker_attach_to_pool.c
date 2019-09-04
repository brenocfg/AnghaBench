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
struct worker_pool {int flags; int /*<<< orphan*/  workers; TYPE_1__* attrs; } ;
struct worker {struct worker_pool* pool; int /*<<< orphan*/  node; int /*<<< orphan*/  flags; int /*<<< orphan*/  task; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int POOL_DISASSOCIATED ; 
 int /*<<< orphan*/  WORKER_UNBOUND ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_pool_attach_mutex ; 

__attribute__((used)) static void worker_attach_to_pool(struct worker *worker,
				   struct worker_pool *pool)
{
	mutex_lock(&wq_pool_attach_mutex);

	/*
	 * set_cpus_allowed_ptr() will fail if the cpumask doesn't have any
	 * online CPUs.  It'll be re-applied when any of the CPUs come up.
	 */
	set_cpus_allowed_ptr(worker->task, pool->attrs->cpumask);

	/*
	 * The wq_pool_attach_mutex ensures %POOL_DISASSOCIATED remains
	 * stable across this function.  See the comments above the flag
	 * definition for details.
	 */
	if (pool->flags & POOL_DISASSOCIATED)
		worker->flags |= WORKER_UNBOUND;

	list_add_tail(&worker->node, &pool->workers);
	worker->pool = pool;

	mutex_unlock(&wq_pool_attach_mutex);
}