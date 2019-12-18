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
struct rpc_wait_queue {int dummy; } ;
struct rpc_task {int /*<<< orphan*/  tk_waitqueue; int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERESTARTSYS ; 
 struct rpc_wait_queue* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_IS_ACTIVATED (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_SIGNALLED ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task_set_status (struct rpc_wait_queue*,struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

void rpc_signal_task(struct rpc_task *task)
{
	struct rpc_wait_queue *queue;

	if (!RPC_IS_ACTIVATED(task))
		return;
	set_bit(RPC_TASK_SIGNALLED, &task->tk_runstate);
	smp_mb__after_atomic();
	queue = READ_ONCE(task->tk_waitqueue);
	if (queue)
		rpc_wake_up_queued_task_set_status(queue, task, -ERESTARTSYS);
}