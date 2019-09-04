#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct worker_pool {int cpu; int id; int /*<<< orphan*/  worker_ida; int /*<<< orphan*/  lock; TYPE_1__* attrs; int /*<<< orphan*/  node; } ;
struct worker {int id; int /*<<< orphan*/  task; TYPE_2__* pool; } ;
typedef  int /*<<< orphan*/  id_buf ;
struct TYPE_4__ {int /*<<< orphan*/  nr_workers; } ;
struct TYPE_3__ {scalar_t__ nice; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct worker* alloc_worker (int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct worker*) ; 
 int /*<<< orphan*/  kthread_bind_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_create_on_node (int /*<<< orphan*/ ,struct worker*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,...) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_attach_to_pool (struct worker*,struct worker_pool*) ; 
 int /*<<< orphan*/  worker_enter_idle (struct worker*) ; 
 int /*<<< orphan*/  worker_thread ; 

__attribute__((used)) static struct worker *create_worker(struct worker_pool *pool)
{
	struct worker *worker = NULL;
	int id = -1;
	char id_buf[16];

	/* ID is needed to determine kthread name */
	id = ida_simple_get(&pool->worker_ida, 0, 0, GFP_KERNEL);
	if (id < 0)
		goto fail;

	worker = alloc_worker(pool->node);
	if (!worker)
		goto fail;

	worker->id = id;

	if (pool->cpu >= 0)
		snprintf(id_buf, sizeof(id_buf), "%d:%d%s", pool->cpu, id,
			 pool->attrs->nice < 0  ? "H" : "");
	else
		snprintf(id_buf, sizeof(id_buf), "u%d:%d", pool->id, id);

	worker->task = kthread_create_on_node(worker_thread, worker, pool->node,
					      "kworker/%s", id_buf);
	if (IS_ERR(worker->task))
		goto fail;

	set_user_nice(worker->task, pool->attrs->nice);
	kthread_bind_mask(worker->task, pool->attrs->cpumask);

	/* successful, attach the worker to the pool */
	worker_attach_to_pool(worker, pool);

	/* start the newly created worker */
	spin_lock_irq(&pool->lock);
	worker->pool->nr_workers++;
	worker_enter_idle(worker);
	wake_up_process(worker->task);
	spin_unlock_irq(&pool->lock);

	return worker;

fail:
	if (id >= 0)
		ida_simple_remove(&pool->worker_ida, id);
	kfree(worker);
	return NULL;
}