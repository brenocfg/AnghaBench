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
struct rpcrdma_ia {scalar_t__ ri_max_inline_read; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; } ;
struct TYPE_2__ {scalar_t__ buflen; } ;
struct rpc_rqst {TYPE_1__ rq_rcv_buf; } ;

/* Variables and functions */

__attribute__((used)) static bool rpcrdma_results_inline(struct rpcrdma_xprt *r_xprt,
				   struct rpc_rqst *rqst)
{
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;

	return rqst->rq_rcv_buf.buflen <= ia->ri_max_inline_read;
}