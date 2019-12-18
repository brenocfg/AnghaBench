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
struct TYPE_3__ {int /*<<< orphan*/  recvs; } ;
struct rpc_xprt {int /*<<< orphan*/  pending; TYPE_1__ stat; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct TYPE_4__ {int len; } ;
struct rpc_rqst {int rq_reply_bytes_recvd; TYPE_2__ rq_private_buf; int /*<<< orphan*/  rq_xid; struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  trace_xprt_complete_rqst (struct rpc_xprt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xprt_request_dequeue_receive_locked (struct rpc_task*) ; 

void xprt_complete_rqst(struct rpc_task *task, int copied)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	dprintk("RPC: %5u xid %08x complete (%d bytes received)\n",
			task->tk_pid, ntohl(req->rq_xid), copied);
	trace_xprt_complete_rqst(xprt, req->rq_xid, copied);

	xprt->stat.recvs++;

	req->rq_private_buf.len = copied;
	/* Ensure all writes are done before we update */
	/* req->rq_reply_bytes_recvd */
	smp_wmb();
	req->rq_reply_bytes_recvd = copied;
	xprt_request_dequeue_receive_locked(task);
	rpc_wake_up_queued_task(&xprt->pending, task);
}