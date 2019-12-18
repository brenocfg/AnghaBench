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
struct TYPE_2__ {int /*<<< orphan*/  bad_reply_count; } ;
struct rpc_xprt {int /*<<< orphan*/  queue_lock; } ;
struct rpcrdma_xprt {TYPE_1__ rx_stats; struct rpc_xprt rx_xprt; } ;
struct rpcrdma_rep {int rr_proc; struct rpc_rqst* rr_rqst; struct rpcrdma_xprt* rr_rxprt; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_task; } ;

/* Variables and functions */
 int EIO ; 
#define  rdma_error 130 
#define  rdma_msg 129 
#define  rdma_nomsg 128 
 int rpcrdma_decode_error (struct rpcrdma_xprt*,struct rpcrdma_rep*,struct rpc_rqst*) ; 
 int rpcrdma_decode_msg (struct rpcrdma_xprt*,struct rpcrdma_rep*,struct rpc_rqst*) ; 
 int rpcrdma_decode_nomsg (struct rpcrdma_xprt*,struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_reply_hdr (struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  xprt_complete_rqst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xprt_unpin_rqst (struct rpc_rqst*) ; 

void rpcrdma_complete_rqst(struct rpcrdma_rep *rep)
{
	struct rpcrdma_xprt *r_xprt = rep->rr_rxprt;
	struct rpc_xprt *xprt = &r_xprt->rx_xprt;
	struct rpc_rqst *rqst = rep->rr_rqst;
	int status;

	switch (rep->rr_proc) {
	case rdma_msg:
		status = rpcrdma_decode_msg(r_xprt, rep, rqst);
		break;
	case rdma_nomsg:
		status = rpcrdma_decode_nomsg(r_xprt, rep);
		break;
	case rdma_error:
		status = rpcrdma_decode_error(r_xprt, rep, rqst);
		break;
	default:
		status = -EIO;
	}
	if (status < 0)
		goto out_badheader;

out:
	spin_lock(&xprt->queue_lock);
	xprt_complete_rqst(rqst->rq_task, status);
	xprt_unpin_rqst(rqst);
	spin_unlock(&xprt->queue_lock);
	return;

/* If the incoming reply terminated a pending RPC, the next
 * RPC call will post a replacement receive buffer as it is
 * being marshaled.
 */
out_badheader:
	trace_xprtrdma_reply_hdr(rep);
	r_xprt->rx_stats.bad_reply_count++;
	goto out;
}