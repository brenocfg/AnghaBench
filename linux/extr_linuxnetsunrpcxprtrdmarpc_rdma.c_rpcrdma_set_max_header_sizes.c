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
struct rpcrdma_ia {unsigned int ri_max_segs; scalar_t__ ri_max_inline_read; scalar_t__ ri_max_inline_write; } ;
struct rpcrdma_create_data_internal {scalar_t__ inline_rsize; scalar_t__ inline_wsize; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; struct rpcrdma_create_data_internal rx_data; } ;

/* Variables and functions */
 scalar_t__ rpcrdma_max_call_header_size (unsigned int) ; 
 scalar_t__ rpcrdma_max_reply_header_size (unsigned int) ; 

void rpcrdma_set_max_header_sizes(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_create_data_internal *cdata = &r_xprt->rx_data;
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	unsigned int maxsegs = ia->ri_max_segs;

	ia->ri_max_inline_write = cdata->inline_wsize -
				  rpcrdma_max_call_header_size(maxsegs);
	ia->ri_max_inline_read = cdata->inline_rsize -
				 rpcrdma_max_reply_header_size(maxsegs);
}