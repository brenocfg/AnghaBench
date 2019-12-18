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
struct TYPE_4__ {scalar_t__ copied; int /*<<< orphan*/  xid; } ;
struct rpc_xprt {int /*<<< orphan*/  queue_lock; } ;
struct sock_xprt {TYPE_2__ recv; struct rpc_xprt xprt; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct rpc_rqst {TYPE_1__ rq_private_buf; int /*<<< orphan*/  rq_task; } ;
struct msghdr {int msg_flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int MSG_EOR ; 
 int MSG_TRUNC ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_complete_rqst (int /*<<< orphan*/ ,scalar_t__) ; 
 struct rpc_rqst* xprt_lookup_rqst (struct rpc_xprt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_pin_rqst (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_unpin_rqst (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xs_read_stream_request (struct sock_xprt*,struct msghdr*,int,struct rpc_rqst*) ; 

__attribute__((used)) static ssize_t
xs_read_stream_reply(struct sock_xprt *transport, struct msghdr *msg, int flags)
{
	struct rpc_xprt *xprt = &transport->xprt;
	struct rpc_rqst *req;
	ssize_t ret = 0;

	/* Look up and lock the request corresponding to the given XID */
	spin_lock(&xprt->queue_lock);
	req = xprt_lookup_rqst(xprt, transport->recv.xid);
	if (!req || (transport->recv.copied && !req->rq_private_buf.len)) {
		msg->msg_flags |= MSG_TRUNC;
		goto out;
	}
	xprt_pin_rqst(req);
	spin_unlock(&xprt->queue_lock);

	ret = xs_read_stream_request(transport, msg, flags, req);

	spin_lock(&xprt->queue_lock);
	if (msg->msg_flags & (MSG_EOR|MSG_TRUNC))
		xprt_complete_rqst(req->rq_task, transport->recv.copied);
	else
		req->rq_private_buf.len = transport->recv.copied;
	xprt_unpin_rqst(req);
out:
	spin_unlock(&xprt->queue_lock);
	return ret;
}