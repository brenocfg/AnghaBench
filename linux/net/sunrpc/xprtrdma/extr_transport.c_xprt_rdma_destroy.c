#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rpcrdma_xprt {int /*<<< orphan*/  rx_ia; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_connect_worker; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_buffer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_ep_destroy (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  rpcrdma_ia_close (int /*<<< orphan*/ *) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 int /*<<< orphan*/  trace_xprtrdma_op_destroy (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  xprt_free (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_rdma_free_addresses (struct rpc_xprt*) ; 

__attribute__((used)) static void
xprt_rdma_destroy(struct rpc_xprt *xprt)
{
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	trace_xprtrdma_op_destroy(r_xprt);

	cancel_delayed_work_sync(&r_xprt->rx_connect_worker);

	rpcrdma_ep_destroy(r_xprt);
	rpcrdma_buffer_destroy(&r_xprt->rx_buf);
	rpcrdma_ia_close(&r_xprt->rx_ia);

	xprt_rdma_free_addresses(xprt);
	xprt_free(xprt);

	module_put(THIS_MODULE);
}