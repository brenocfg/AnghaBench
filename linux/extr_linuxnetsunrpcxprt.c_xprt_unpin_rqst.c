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
struct rpc_task {int /*<<< orphan*/  tk_runstate; } ;
struct rpc_rqst {struct rpc_task* rq_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_MSG_RECV ; 
 int /*<<< orphan*/  RPC_TASK_MSG_RECV_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xprt_unpin_rqst(struct rpc_rqst *req)
{
	struct rpc_task *task = req->rq_task;

	clear_bit(RPC_TASK_MSG_RECV, &task->tk_runstate);
	if (test_bit(RPC_TASK_MSG_RECV_WAIT, &task->tk_runstate))
		wake_up_bit(&task->tk_runstate, RPC_TASK_MSG_RECV);
}