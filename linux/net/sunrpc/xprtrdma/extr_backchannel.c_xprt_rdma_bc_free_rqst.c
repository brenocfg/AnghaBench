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
struct rpcrdma_req {int /*<<< orphan*/ * rl_reply; } ;
struct rpc_xprt {int /*<<< orphan*/  bc_pa_lock; int /*<<< orphan*/  bc_pa_list; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_bc_pa_list; struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 int /*<<< orphan*/  rpcrdma_recv_buffer_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 

void xprt_rdma_bc_free_rqst(struct rpc_rqst *rqst)
{
	struct rpcrdma_req *req = rpcr_to_rdmar(rqst);
	struct rpc_xprt *xprt = rqst->rq_xprt;

	rpcrdma_recv_buffer_put(req->rl_reply);
	req->rl_reply = NULL;

	spin_lock(&xprt->bc_pa_lock);
	list_add_tail(&rqst->rq_bc_pa_list, &xprt->bc_pa_list);
	spin_unlock(&xprt->bc_pa_lock);
	xprt_put(xprt);
}