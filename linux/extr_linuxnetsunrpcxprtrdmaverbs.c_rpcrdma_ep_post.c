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
struct rpcrdma_req {int /*<<< orphan*/  rl_flags; TYPE_2__* rl_sendctx; } ;
struct rpcrdma_ia {TYPE_1__* ri_ops; } ;
struct rpcrdma_ep {scalar_t__ rep_send_count; scalar_t__ rep_send_batch; } ;
struct ib_send_wr {int /*<<< orphan*/  send_flags; } ;
struct TYPE_4__ {struct ib_send_wr sc_wr; } ;
struct TYPE_3__ {int (* ro_send ) (struct rpcrdma_ia*,struct rpcrdma_req*) ;} ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  RPCRDMA_REQ_F_TX_RESOURCES ; 
 int stub1 (struct rpcrdma_ia*,struct rpcrdma_req*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_post_send (struct rpcrdma_req*,int) ; 

int
rpcrdma_ep_post(struct rpcrdma_ia *ia,
		struct rpcrdma_ep *ep,
		struct rpcrdma_req *req)
{
	struct ib_send_wr *send_wr = &req->rl_sendctx->sc_wr;
	int rc;

	if (!ep->rep_send_count ||
	    test_bit(RPCRDMA_REQ_F_TX_RESOURCES, &req->rl_flags)) {
		send_wr->send_flags |= IB_SEND_SIGNALED;
		ep->rep_send_count = ep->rep_send_batch;
	} else {
		send_wr->send_flags &= ~IB_SEND_SIGNALED;
		--ep->rep_send_count;
	}

	rc = ia->ri_ops->ro_send(ia, req);
	trace_xprtrdma_post_send(req, rc);
	if (rc)
		return -ENOTCONN;
	return 0;
}