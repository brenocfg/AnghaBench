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
struct rpcrdma_req {int /*<<< orphan*/  rl_flags; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRDMA_REQ_F_PENDING ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 int /*<<< orphan*/  rpcrdma_release_rqst (struct rpcrdma_xprt*,struct rpcrdma_req*) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_rpc_done (struct rpc_task*,struct rpcrdma_req*) ; 

__attribute__((used)) static void
xprt_rdma_free(struct rpc_task *task)
{
	struct rpc_rqst *rqst = task->tk_rqstp;
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(rqst->rq_xprt);
	struct rpcrdma_req *req = rpcr_to_rdmar(rqst);

	if (test_bit(RPCRDMA_REQ_F_PENDING, &req->rl_flags))
		rpcrdma_release_rqst(r_xprt, req);
	trace_xprtrdma_rpc_done(task, req);
}