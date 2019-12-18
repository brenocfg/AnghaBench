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
struct rpc_xprt {int /*<<< orphan*/  timer; int /*<<< orphan*/  queue_lock; } ;
struct rpc_task {int /*<<< orphan*/  tk_runstate; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; int /*<<< orphan*/  rq_private_buf; struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_NEED_RECV ; 
 int /*<<< orphan*/  del_singleshot_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_request_need_enqueue_receive (struct rpc_task*,struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_request_prepare (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_request_rb_insert (struct rpc_xprt*,struct rpc_rqst*) ; 

void
xprt_request_enqueue_receive(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	if (!xprt_request_need_enqueue_receive(task, req))
		return;

	xprt_request_prepare(task->tk_rqstp);
	spin_lock(&xprt->queue_lock);

	/* Update the softirq receive buffer */
	memcpy(&req->rq_private_buf, &req->rq_rcv_buf,
			sizeof(req->rq_private_buf));

	/* Add request to the receive list */
	xprt_request_rb_insert(xprt, req);
	set_bit(RPC_TASK_NEED_RECV, &task->tk_runstate);
	spin_unlock(&xprt->queue_lock);

	/* Turn off autodisconnect */
	del_singleshot_timer_sync(&xprt->timer);
}