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
struct rpcrdma_xprt {int dummy; } ;
struct rpcrdma_req {TYPE_2__* rl_recvbuf; TYPE_1__* rl_sendbuf; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rbuffer; int /*<<< orphan*/  rq_buffer; int /*<<< orphan*/  rq_rcvsize; int /*<<< orphan*/  rq_callsize; int /*<<< orphan*/  rq_xprt; } ;
typedef  int gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  rg_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  rg_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_NOWAIT ; 
 int RPCRDMA_DEF_GFP ; 
 scalar_t__ RPC_IS_SWAPPER (struct rpc_task*) ; 
 int __GFP_MEMALLOC ; 
 int __GFP_NOWARN ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 int /*<<< orphan*/  rpcrdma_get_recvbuf (struct rpcrdma_xprt*,struct rpcrdma_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpcrdma_get_sendbuf (struct rpcrdma_xprt*,struct rpcrdma_req*,int /*<<< orphan*/ ,int) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xprtrdma_allocate (struct rpc_task*,struct rpcrdma_req*) ; 

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

	if (!rpcrdma_get_sendbuf(r_xprt, req, rqst->rq_callsize, flags))
		goto out_fail;
	if (!rpcrdma_get_recvbuf(r_xprt, req, rqst->rq_rcvsize, flags))
		goto out_fail;

	rqst->rq_buffer = req->rl_sendbuf->rg_base;
	rqst->rq_rbuffer = req->rl_recvbuf->rg_base;
	trace_xprtrdma_allocate(task, req);
	return 0;

out_fail:
	trace_xprtrdma_allocate(task, NULL);
	return -ENOMEM;
}