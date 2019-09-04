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
typedef  int u32 ;
struct xdr_buf {int /*<<< orphan*/  len; struct kvec* head; } ;
struct TYPE_3__ {int rb_bc_max_requests; } ;
struct rpcrdma_xprt {TYPE_1__ rx_buf; } ;
struct rpc_xprt {unsigned long cwnd; int /*<<< orphan*/  recv_lock; int /*<<< orphan*/  transport_lock; } ;
struct TYPE_4__ {struct kvec* head; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_task; int /*<<< orphan*/  rq_rcv_buf; TYPE_2__ rq_private_buf; } ;
struct kvec {size_t iov_len; TYPE_2__* iov_base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EAGAIN ; 
 int RPC_CWNDSHIFT ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*,size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_complete_rqst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rpc_rqst* xprt_lookup_rqst (struct rpc_xprt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_release_rqst_cong (int /*<<< orphan*/ ) ; 

int svc_rdma_handle_bc_reply(struct rpc_xprt *xprt, __be32 *rdma_resp,
			     struct xdr_buf *rcvbuf)
{
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	struct kvec *dst, *src = &rcvbuf->head[0];
	struct rpc_rqst *req;
	unsigned long cwnd;
	u32 credits;
	size_t len;
	__be32 xid;
	__be32 *p;
	int ret;

	p = (__be32 *)src->iov_base;
	len = src->iov_len;
	xid = *rdma_resp;

#ifdef SVCRDMA_BACKCHANNEL_DEBUG
	pr_info("%s: xid=%08x, length=%zu\n",
		__func__, be32_to_cpu(xid), len);
	pr_info("%s: RPC/RDMA: %*ph\n",
		__func__, (int)RPCRDMA_HDRLEN_MIN, rdma_resp);
	pr_info("%s:      RPC: %*ph\n",
		__func__, (int)len, p);
#endif

	ret = -EAGAIN;
	if (src->iov_len < 24)
		goto out_shortreply;

	spin_lock(&xprt->recv_lock);
	req = xprt_lookup_rqst(xprt, xid);
	if (!req)
		goto out_notfound;

	dst = &req->rq_private_buf.head[0];
	memcpy(&req->rq_private_buf, &req->rq_rcv_buf, sizeof(struct xdr_buf));
	if (dst->iov_len < len)
		goto out_unlock;
	memcpy(dst->iov_base, p, len);

	credits = be32_to_cpup(rdma_resp + 2);
	if (credits == 0)
		credits = 1;	/* don't deadlock */
	else if (credits > r_xprt->rx_buf.rb_bc_max_requests)
		credits = r_xprt->rx_buf.rb_bc_max_requests;

	spin_lock_bh(&xprt->transport_lock);
	cwnd = xprt->cwnd;
	xprt->cwnd = credits << RPC_CWNDSHIFT;
	if (xprt->cwnd > cwnd)
		xprt_release_rqst_cong(req->rq_task);
	spin_unlock_bh(&xprt->transport_lock);


	ret = 0;
	xprt_complete_rqst(req->rq_task, rcvbuf->len);
	rcvbuf->len = 0;

out_unlock:
	spin_unlock(&xprt->recv_lock);
out:
	return ret;

out_shortreply:
	dprintk("svcrdma: short bc reply: xprt=%p, len=%zu\n",
		xprt, src->iov_len);
	goto out;

out_notfound:
	dprintk("svcrdma: unrecognized bc reply: xprt=%p, xid=%08x\n",
		xprt, be32_to_cpu(xid));
	goto out_unlock;
}