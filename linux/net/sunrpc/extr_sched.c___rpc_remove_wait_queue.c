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
struct rpc_wait_queue {int /*<<< orphan*/  qlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ tk_wait; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ RPC_IS_PRIORITY (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  __rpc_disable_timer (struct rpc_wait_queue*,struct rpc_task*) ; 
 int /*<<< orphan*/  __rpc_remove_wait_queue_priority (struct rpc_task*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_wait_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_qname (struct rpc_wait_queue*) ; 

__attribute__((used)) static void __rpc_remove_wait_queue(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	__rpc_disable_timer(queue, task);
	if (RPC_IS_PRIORITY(queue))
		__rpc_remove_wait_queue_priority(task);
	else
		list_del(&task->u.tk_wait.list);
	queue->qlen--;
	dprintk("RPC: %5u removed from queue %p \"%s\"\n",
			task->tk_pid, queue, rpc_qname(queue));
}