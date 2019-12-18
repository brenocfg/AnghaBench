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
struct rpc_xprt {int /*<<< orphan*/  cong; int /*<<< orphan*/  cwnd; } ;
struct rpc_rqst {int rq_cong; TYPE_1__* rq_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  tk_pid; } ;

/* Variables and functions */
 scalar_t__ RPCXPRT_CONGESTED (struct rpc_xprt*) ; 
 scalar_t__ RPC_CWNDSCALE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_set_congestion_window_wait (struct rpc_xprt*) ; 

__attribute__((used)) static int
__xprt_get_cong(struct rpc_xprt *xprt, struct rpc_rqst *req)
{
	if (req->rq_cong)
		return 1;
	dprintk("RPC: %5u xprt_cwnd_limited cong = %lu cwnd = %lu\n",
			req->rq_task->tk_pid, xprt->cong, xprt->cwnd);
	if (RPCXPRT_CONGESTED(xprt)) {
		xprt_set_congestion_window_wait(xprt);
		return 0;
	}
	req->rq_cong = 1;
	xprt->cong += RPC_CWNDSCALE;
	return 1;
}