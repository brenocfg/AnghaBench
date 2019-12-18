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
struct rpcrdma_req {int /*<<< orphan*/  rl_recvbuf; int /*<<< orphan*/  rl_sendbuf; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {void* rq_rbuffer; void* rq_buffer; int /*<<< orphan*/  rq_rcvsize; int /*<<< orphan*/  rq_callsize; int /*<<< orphan*/  rq_xprt; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_NOWAIT ; 
 int RPCRDMA_DEF_GFP ; 
 scalar_t__ RPC_IS_SWAPPER (struct rpc_task*) ; 
 int __GFP_MEMALLOC ; 
 int __GFP_NOWARN ; 
 void* rdmab_data (int /*<<< orphan*/ ) ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 int /*<<< orphan*/  rpcrdma_check_regbuf (struct rpcrdma_xprt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xprtrdma_op_allocate (struct rpc_task*,struct rpcrdma_req*) ; 

__attribute__((used)) static int
xprt_rdma_allocate(struct rpc_task *task)
{
	struct rpc_rqst *rqst = task->tk_rqstp;
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(rqst->rq_xprt);
	struct rpcrdma_req *req = rpcr_to_rdmar(rqst);
	gfp_t flags;

	flags = RPCRDMA_DEF_GFP;
	if (RPC_IS_SWAPPER(task))
		flags = __GFP_MEMALLOC | GFP_NOWAIT | __GFP_NOWARN;

	if (!rpcrdma_check_regbuf(r_xprt, req->rl_sendbuf, rqst->rq_callsize,
				  flags))
		goto out_fail;
	if (!rpcrdma_check_regbuf(r_xprt, req->rl_recvbuf, rqst->rq_rcvsize,
				  flags))
		goto out_fail;

	rqst->rq_buffer = rdmab_data(req->rl_sendbuf);
	rqst->rq_rbuffer = rdmab_data(req->rl_recvbuf);
	trace_xprtrdma_op_allocate(task, req);
	return 0;

out_fail:
	trace_xprtrdma_op_allocate(task, NULL);
	return -ENOMEM;
}