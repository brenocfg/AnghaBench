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
struct TYPE_2__ {int rb_credits; } ;
struct rpcrdma_ia {int /*<<< orphan*/  ri_flags; } ;
struct rpcrdma_ep {int /*<<< orphan*/  rep_connected; } ;
struct rpcrdma_xprt {TYPE_1__ rx_buf; struct rpcrdma_ia rx_ia; struct rpcrdma_ep rx_ep; } ;
struct rpc_xprt {int /*<<< orphan*/  connect_cookie; scalar_t__ reestablish_timeout; int /*<<< orphan*/  cwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  RPCRDMA_IAF_REMOVING ; 
 int /*<<< orphan*/  RPC_CWNDSHIFT ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rpcrdma_ep_disconnect (struct rpcrdma_ep*,struct rpcrdma_ia*) ; 
 int /*<<< orphan*/  rpcrdma_ia_remove (struct rpcrdma_ia*) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_op_close (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  xprt_clear_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_disconnect_done (struct rpc_xprt*) ; 

void xprt_rdma_close(struct rpc_xprt *xprt)
{
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	struct rpcrdma_ep *ep = &r_xprt->rx_ep;
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;

	might_sleep();

	trace_xprtrdma_op_close(r_xprt);

	/* Prevent marshaling and sending of new requests */
	xprt_clear_connected(xprt);

	if (test_and_clear_bit(RPCRDMA_IAF_REMOVING, &ia->ri_flags)) {
		rpcrdma_ia_remove(ia);
		goto out;
	}

	if (ep->rep_connected == -ENODEV)
		return;
	rpcrdma_ep_disconnect(ep, ia);

	/* Prepare @xprt for the next connection by reinitializing
	 * its credit grant to one (see RFC 8166, Section 3.3.3).
	 */
	r_xprt->rx_buf.rb_credits = 1;
	xprt->cwnd = RPC_CWNDSHIFT;

out:
	xprt->reestablish_timeout = 0;
	++xprt->connect_cookie;
	xprt_disconnect_done(xprt);
}