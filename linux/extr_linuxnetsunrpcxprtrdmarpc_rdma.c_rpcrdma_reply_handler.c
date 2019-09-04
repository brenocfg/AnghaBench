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
struct rpcrdma_buffer {int rb_max_requests; int rb_credits; int /*<<< orphan*/  rb_posted_receives; } ;
struct rpc_xprt {int /*<<< orphan*/  recv_lock; } ;
struct rpcrdma_xprt {struct rpcrdma_buffer rx_buf; struct rpc_xprt rx_xprt; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_flags; struct rpcrdma_rep* rl_reply; } ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct rpcrdma_rep {scalar_t__ rr_vers; int /*<<< orphan*/  rr_work; struct rpc_rqst* rr_rqst; int /*<<< orphan*/  rr_xid; int /*<<< orphan*/  rr_proc; int /*<<< orphan*/  rr_stream; TYPE_2__ rr_hdrbuf; struct rpcrdma_xprt* rr_rxprt; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_task; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRDMA_REQ_F_PENDING ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 scalar_t__ rpcrdma_is_bcall (struct rpcrdma_xprt*,struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  rpcrdma_post_recvs (struct rpcrdma_xprt*,int) ; 
 int /*<<< orphan*/  rpcrdma_receive_wq ; 
 int /*<<< orphan*/  rpcrdma_recv_buffer_put (struct rpcrdma_rep*) ; 
 scalar_t__ rpcrdma_version ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_reply (int /*<<< orphan*/ ,struct rpcrdma_rep*,struct rpcrdma_req*,int) ; 
 int /*<<< orphan*/  trace_xprtrdma_reply_rqst (struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  trace_xprtrdma_reply_short (struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  trace_xprtrdma_reply_vers (struct rpcrdma_rep*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_init_decode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (int /*<<< orphan*/ *,int) ; 
 struct rpc_rqst* xprt_lookup_rqst (struct rpc_xprt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_pin_rqst (struct rpc_rqst*) ; 

void rpcrdma_reply_handler(struct rpcrdma_rep *rep)
{
	struct rpcrdma_xprt *r_xprt = rep->rr_rxprt;
	struct rpc_xprt *xprt = &r_xprt->rx_xprt;
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;
	struct rpcrdma_req *req;
	struct rpc_rqst *rqst;
	u32 credits;
	__be32 *p;

	--buf->rb_posted_receives;

	if (rep->rr_hdrbuf.head[0].iov_len == 0)
		goto out_badstatus;

	/* Fixed transport header fields */
	xdr_init_decode(&rep->rr_stream, &rep->rr_hdrbuf,
			rep->rr_hdrbuf.head[0].iov_base);
	p = xdr_inline_decode(&rep->rr_stream, 4 * sizeof(*p));
	if (unlikely(!p))
		goto out_shortreply;
	rep->rr_xid = *p++;
	rep->rr_vers = *p++;
	credits = be32_to_cpu(*p++);
	rep->rr_proc = *p++;

	if (rep->rr_vers != rpcrdma_version)
		goto out_badversion;

	if (rpcrdma_is_bcall(r_xprt, rep))
		return;

	/* Match incoming rpcrdma_rep to an rpcrdma_req to
	 * get context for handling any incoming chunks.
	 */
	spin_lock(&xprt->recv_lock);
	rqst = xprt_lookup_rqst(xprt, rep->rr_xid);
	if (!rqst)
		goto out_norqst;
	xprt_pin_rqst(rqst);

	if (credits == 0)
		credits = 1;	/* don't deadlock */
	else if (credits > buf->rb_max_requests)
		credits = buf->rb_max_requests;
	buf->rb_credits = credits;

	spin_unlock(&xprt->recv_lock);

	req = rpcr_to_rdmar(rqst);
	req->rl_reply = rep;
	rep->rr_rqst = rqst;
	clear_bit(RPCRDMA_REQ_F_PENDING, &req->rl_flags);

	trace_xprtrdma_reply(rqst->rq_task, rep, req, credits);

	rpcrdma_post_recvs(r_xprt, false);
	queue_work(rpcrdma_receive_wq, &rep->rr_work);
	return;

out_badversion:
	trace_xprtrdma_reply_vers(rep);
	goto repost;

/* The RPC transaction has already been terminated, or the header
 * is corrupt.
 */
out_norqst:
	spin_unlock(&xprt->recv_lock);
	trace_xprtrdma_reply_rqst(rep);
	goto repost;

out_shortreply:
	trace_xprtrdma_reply_short(rep);

/* If no pending RPC transaction was matched, post a replacement
 * receive buffer before returning.
 */
repost:
	rpcrdma_post_recvs(r_xprt, false);
out_badstatus:
	rpcrdma_recv_buffer_put(rep);
}