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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct rpc_xprt {int /*<<< orphan*/  recv_lock; } ;
struct rpc_task {int dummy; } ;
struct TYPE_2__ {int buflen; } ;
struct rpc_rqst {TYPE_1__ rq_private_buf; struct rpc_task* rq_task; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;
typedef  int /*<<< orphan*/  _xid ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_complete_rqst (struct rpc_task*,int) ; 
 struct rpc_rqst* xprt_lookup_rqst (struct rpc_xprt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_pin_rqst (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_unpin_rqst (struct rpc_rqst*) ; 
 scalar_t__ xs_local_copy_to_xdr (TYPE_1__*,struct sk_buff*) ; 

__attribute__((used)) static void xs_local_data_read_skb(struct rpc_xprt *xprt,
		struct sock *sk,
		struct sk_buff *skb)
{
	struct rpc_task *task;
	struct rpc_rqst *rovr;
	int repsize, copied;
	u32 _xid;
	__be32 *xp;

	repsize = skb->len - sizeof(rpc_fraghdr);
	if (repsize < 4) {
		dprintk("RPC:       impossible RPC reply size %d\n", repsize);
		return;
	}

	/* Copy the XID from the skb... */
	xp = skb_header_pointer(skb, sizeof(rpc_fraghdr), sizeof(_xid), &_xid);
	if (xp == NULL)
		return;

	/* Look up and lock the request corresponding to the given XID */
	spin_lock(&xprt->recv_lock);
	rovr = xprt_lookup_rqst(xprt, *xp);
	if (!rovr)
		goto out_unlock;
	xprt_pin_rqst(rovr);
	spin_unlock(&xprt->recv_lock);
	task = rovr->rq_task;

	copied = rovr->rq_private_buf.buflen;
	if (copied > repsize)
		copied = repsize;

	if (xs_local_copy_to_xdr(&rovr->rq_private_buf, skb)) {
		dprintk("RPC:       sk_buff copy failed\n");
		spin_lock(&xprt->recv_lock);
		goto out_unpin;
	}

	spin_lock(&xprt->recv_lock);
	xprt_complete_rqst(task, copied);
out_unpin:
	xprt_unpin_rqst(rovr);
 out_unlock:
	spin_unlock(&xprt->recv_lock);
}