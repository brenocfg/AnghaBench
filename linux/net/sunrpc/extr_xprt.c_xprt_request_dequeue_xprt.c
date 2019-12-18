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
struct rpc_xprt {int /*<<< orphan*/  queue_lock; } ;
struct rpc_task {int /*<<< orphan*/  tk_runstate; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_MSG_PIN_WAIT ; 
 int /*<<< orphan*/  RPC_TASK_NEED_RECV ; 
 int /*<<< orphan*/  RPC_TASK_NEED_XMIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xprt_is_pinned_rqst (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_request_dequeue_receive_locked (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_request_dequeue_transmit_locked (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_wait_on_pinned_rqst (struct rpc_rqst*) ; 

void
xprt_request_dequeue_xprt(struct rpc_task *task)
{
	struct rpc_rqst	*req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	if (test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate) ||
	    test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate) ||
	    xprt_is_pinned_rqst(req)) {
		spin_lock(&xprt->queue_lock);
		xprt_request_dequeue_transmit_locked(task);
		xprt_request_dequeue_receive_locked(task);
		while (xprt_is_pinned_rqst(req)) {
			set_bit(RPC_TASK_MSG_PIN_WAIT, &task->tk_runstate);
			spin_unlock(&xprt->queue_lock);
			xprt_wait_on_pinned_rqst(req);
			spin_lock(&xprt->queue_lock);
			clear_bit(RPC_TASK_MSG_PIN_WAIT, &task->tk_runstate);
		}
		spin_unlock(&xprt->queue_lock);
	}
}