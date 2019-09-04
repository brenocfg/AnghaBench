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
struct TYPE_2__ {scalar_t__ rep_connected; } ;
struct rpcrdma_xprt {int /*<<< orphan*/  rx_connect_worker; TYPE_1__ rx_ep; } ;
struct rpc_xprt {int reestablish_timeout; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int RPCRDMA_INIT_REEST_TO ; 
 int RPCRDMA_MAX_REEST_TO ; 
 int /*<<< orphan*/  RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
xprt_rdma_connect(struct rpc_xprt *xprt, struct rpc_task *task)
{
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	if (r_xprt->rx_ep.rep_connected != 0) {
		/* Reconnect */
		schedule_delayed_work(&r_xprt->rx_connect_worker,
				      xprt->reestablish_timeout);
		xprt->reestablish_timeout <<= 1;
		if (xprt->reestablish_timeout > RPCRDMA_MAX_REEST_TO)
			xprt->reestablish_timeout = RPCRDMA_MAX_REEST_TO;
		else if (xprt->reestablish_timeout < RPCRDMA_INIT_REEST_TO)
			xprt->reestablish_timeout = RPCRDMA_INIT_REEST_TO;
	} else {
		schedule_delayed_work(&r_xprt->rx_connect_worker, 0);
		if (!RPC_IS_ASYNC(task))
			flush_delayed_work(&r_xprt->rx_connect_worker);
	}
}