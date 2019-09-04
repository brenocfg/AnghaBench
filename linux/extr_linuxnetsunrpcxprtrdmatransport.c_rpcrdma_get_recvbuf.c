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
struct TYPE_2__ {size_t hardway_register_count; } ;
struct rpcrdma_xprt {TYPE_1__ rx_stats; } ;
struct rpcrdma_req {struct rpcrdma_regbuf* rl_recvbuf; } ;
struct rpcrdma_regbuf {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 scalar_t__ IS_ERR (struct rpcrdma_regbuf*) ; 
 size_t rdmab_length (struct rpcrdma_regbuf*) ; 
 struct rpcrdma_regbuf* rpcrdma_alloc_regbuf (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_free_regbuf (struct rpcrdma_regbuf*) ; 

__attribute__((used)) static bool
rpcrdma_get_recvbuf(struct rpcrdma_xprt *r_xprt, struct rpcrdma_req *req,
		    size_t size, gfp_t flags)
{
	struct rpcrdma_regbuf *rb;

	if (req->rl_recvbuf && rdmab_length(req->rl_recvbuf) >= size)
		return true;

	rb = rpcrdma_alloc_regbuf(size, DMA_NONE, flags);
	if (IS_ERR(rb))
		return false;

	rpcrdma_free_regbuf(req->rl_recvbuf);
	r_xprt->rx_stats.hardway_register_count += size;
	req->rl_recvbuf = rb;
	return true;
}