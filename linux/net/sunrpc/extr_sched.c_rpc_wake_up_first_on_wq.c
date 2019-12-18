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
struct workqueue_struct {int dummy; } ;
struct rpc_wait_queue {int /*<<< orphan*/  lock; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 struct rpc_task* __rpc_find_next_queued (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_wait_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_qname (struct rpc_wait_queue*) ; 
 struct rpc_task* rpc_wake_up_task_on_wq_queue_action_locked (struct workqueue_struct*,struct rpc_wait_queue*,struct rpc_task*,int (*) (struct rpc_task*,void*),void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct rpc_task *rpc_wake_up_first_on_wq(struct workqueue_struct *wq,
		struct rpc_wait_queue *queue,
		bool (*func)(struct rpc_task *, void *), void *data)
{
	struct rpc_task	*task = NULL;

	dprintk("RPC:       wake_up_first(%p \"%s\")\n",
			queue, rpc_qname(queue));
	spin_lock(&queue->lock);
	task = __rpc_find_next_queued(queue);
	if (task != NULL)
		task = rpc_wake_up_task_on_wq_queue_action_locked(wq, queue,
				task, func, data);
	spin_unlock(&queue->lock);

	return task;
}