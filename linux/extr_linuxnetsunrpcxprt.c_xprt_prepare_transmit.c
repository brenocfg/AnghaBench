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
struct rpc_xprt {scalar_t__ connect_cookie; int /*<<< orphan*/  transport_lock; TYPE_1__* ops; int /*<<< orphan*/  pending; } ;
struct rpc_task {int tk_flags; scalar_t__ tk_status; int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {scalar_t__ rq_connect_cookie; scalar_t__ rq_reply_bytes_recvd; int /*<<< orphan*/  rq_bytes_sent; struct rpc_xprt* rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reserve_xprt ) (struct rpc_xprt*,struct rpc_task*) ;int /*<<< orphan*/  (* set_retrans_timeout ) (struct rpc_task*) ;} ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int RPC_TASK_NO_RETRANS_TIMEOUT ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*) ; 
 int /*<<< orphan*/  stub2 (struct rpc_xprt*,struct rpc_task*) ; 
 scalar_t__ xprt_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_timer ; 

bool xprt_prepare_transmit(struct rpc_task *task)
{
	struct rpc_rqst	*req = task->tk_rqstp;
	struct rpc_xprt	*xprt = req->rq_xprt;
	bool ret = false;

	dprintk("RPC: %5u xprt_prepare_transmit\n", task->tk_pid);

	spin_lock_bh(&xprt->transport_lock);
	if (!req->rq_bytes_sent) {
		if (req->rq_reply_bytes_recvd) {
			task->tk_status = req->rq_reply_bytes_recvd;
			goto out_unlock;
		}
		if ((task->tk_flags & RPC_TASK_NO_RETRANS_TIMEOUT)
		    && xprt_connected(xprt)
		    && req->rq_connect_cookie == xprt->connect_cookie) {
			xprt->ops->set_retrans_timeout(task);
			rpc_sleep_on(&xprt->pending, task, xprt_timer);
			goto out_unlock;
		}
	}
	if (!xprt->ops->reserve_xprt(xprt, task)) {
		task->tk_status = -EAGAIN;
		goto out_unlock;
	}
	ret = true;
out_unlock:
	spin_unlock_bh(&xprt->transport_lock);
	return ret;
}