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
struct rpcrdma_xprt {int dummy; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_registered; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  frwr_unmap_sync (struct rpcrdma_xprt*,struct rpcrdma_req*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xprtrdma_op_free (struct rpc_task*,struct rpcrdma_req*) ; 

__attribute__((used)) static void
xprt_rdma_free(struct rpc_task *task)
{
	struct rpc_rqst *rqst = task->tk_rqstp;
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(rqst->rq_xprt);
	struct rpcrdma_req *req = rpcr_to_rdmar(rqst);

	trace_xprtrdma_op_free(task, req);

	if (!list_empty(&req->rl_registered))
		frwr_unmap_sync(r_xprt, req);

	/* XXX: If the RPC is completing because of a signal and
	 * not because a reply was received, we ought to ensure
	 * that the Send completion has fired, so that memory
	 * involved with the Send is not still visible to the NIC.
	 */
}