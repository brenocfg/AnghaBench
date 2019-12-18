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
struct TYPE_4__ {scalar_t__ rep_max_inline_recv; } ;
struct rpcrdma_xprt {TYPE_2__ rx_ep; } ;
struct TYPE_3__ {scalar_t__ buflen; } ;
struct rpc_rqst {TYPE_1__ rq_rcv_buf; } ;

/* Variables and functions */

__attribute__((used)) static bool rpcrdma_results_inline(struct rpcrdma_xprt *r_xprt,
				   struct rpc_rqst *rqst)
{
	return rqst->rq_rcv_buf.buflen <= r_xprt->rx_ep.rep_max_inline_recv;
}