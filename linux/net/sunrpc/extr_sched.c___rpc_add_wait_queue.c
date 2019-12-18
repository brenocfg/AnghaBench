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
struct rpc_wait_queue {int /*<<< orphan*/  qlen; int /*<<< orphan*/ * tasks; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  timer_list; } ;
struct TYPE_4__ {TYPE_1__ tk_wait; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; struct rpc_wait_queue* tk_waitqueue; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ RPC_IS_PRIORITY (struct rpc_wait_queue*) ; 
 scalar_t__ RPC_IS_QUEUED (struct rpc_task*) ; 
 scalar_t__ RPC_IS_SWAPPER (struct rpc_task*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  __rpc_add_wait_queue_priority (struct rpc_wait_queue*,struct rpc_task*,unsigned char) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_wait_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_qname (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  rpc_set_queued (struct rpc_task*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void __rpc_add_wait_queue(struct rpc_wait_queue *queue,
		struct rpc_task *task,
		unsigned char queue_priority)
{
	WARN_ON_ONCE(RPC_IS_QUEUED(task));
	if (RPC_IS_QUEUED(task))
		return;

	INIT_LIST_HEAD(&task->u.tk_wait.timer_list);
	if (RPC_IS_PRIORITY(queue))
		__rpc_add_wait_queue_priority(queue, task, queue_priority);
	else if (RPC_IS_SWAPPER(task))
		list_add(&task->u.tk_wait.list, &queue->tasks[0]);
	else
		list_add_tail(&task->u.tk_wait.list, &queue->tasks[0]);
	task->tk_waitqueue = queue;
	queue->qlen++;
	/* barrier matches the read in rpc_wake_up_task_queue_locked() */
	smp_wmb();
	rpc_set_queued(task);

	dprintk("RPC: %5u added to queue %p \"%s\"\n",
			task->tk_pid, queue, rpc_qname(queue));
}