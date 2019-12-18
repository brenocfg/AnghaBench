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
struct rpc_wait_queue {int dummy; } ;
struct rpc_task {struct rpc_wait_queue* tk_waitqueue; } ;

/* Variables and functions */
 scalar_t__ RPC_IS_QUEUED (struct rpc_task*) ; 
 int /*<<< orphan*/  __rpc_do_wake_up_task_on_wq (struct workqueue_struct*,struct rpc_wait_queue*,struct rpc_task*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static struct rpc_task *
rpc_wake_up_task_on_wq_queue_action_locked(struct workqueue_struct *wq,
		struct rpc_wait_queue *queue, struct rpc_task *task,
		bool (*action)(struct rpc_task *, void *), void *data)
{
	if (RPC_IS_QUEUED(task)) {
		smp_rmb();
		if (task->tk_waitqueue == queue) {
			if (action == NULL || action(task, data)) {
				__rpc_do_wake_up_task_on_wq(wq, queue, task);
				return task;
			}
		}
	}
	return NULL;
}