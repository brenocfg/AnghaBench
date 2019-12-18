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
struct rpcrdma_xprt {int /*<<< orphan*/  rx_buf; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_slot; } ;
struct rpc_xprt {int /*<<< orphan*/  backlog; int /*<<< orphan*/  state; } ;
struct rpc_task {int /*<<< orphan*/  tk_status; int /*<<< orphan*/ * tk_rqstp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  XPRT_CONGESTED ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 struct rpcrdma_req* rpcrdma_buffer_get (int /*<<< orphan*/ *) ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xprt_rdma_alloc_slot(struct rpc_xprt *xprt, struct rpc_task *task)
{
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	struct rpcrdma_req *req;

	req = rpcrdma_buffer_get(&r_xprt->rx_buf);
	if (!req)
		goto out_sleep;
	task->tk_rqstp = &req->rl_slot;
	task->tk_status = 0;
	return;

out_sleep:
	set_bit(XPRT_CONGESTED, &xprt->state);
	rpc_sleep_on(&xprt->backlog, task, NULL);
	task->tk_status = -EAGAIN;
}