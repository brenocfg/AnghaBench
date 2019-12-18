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
struct rpcrdma_ep {scalar_t__ rep_inline_recv; scalar_t__ rep_max_inline_recv; scalar_t__ rep_inline_send; scalar_t__ rep_max_inline_send; } ;
struct TYPE_2__ {unsigned int ri_max_segs; } ;
struct rpcrdma_xprt {struct rpcrdma_ep rx_ep; TYPE_1__ rx_ia; } ;

/* Variables and functions */
 scalar_t__ rpcrdma_max_call_header_size (unsigned int) ; 
 scalar_t__ rpcrdma_max_reply_header_size (unsigned int) ; 

void rpcrdma_set_max_header_sizes(struct rpcrdma_xprt *r_xprt)
{
	unsigned int maxsegs = r_xprt->rx_ia.ri_max_segs;
	struct rpcrdma_ep *ep = &r_xprt->rx_ep;

	ep->rep_max_inline_send =
		ep->rep_inline_send - rpcrdma_max_call_header_size(maxsegs);
	ep->rep_max_inline_recv =
		ep->rep_inline_recv - rpcrdma_max_reply_header_size(maxsegs);
}