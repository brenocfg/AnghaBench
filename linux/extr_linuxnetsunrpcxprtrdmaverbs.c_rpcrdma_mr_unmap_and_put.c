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
struct TYPE_2__ {int /*<<< orphan*/  ri_device; } ;
struct rpcrdma_xprt {int /*<<< orphan*/  rx_buf; TYPE_1__ rx_ia; } ;
struct rpcrdma_mr {int /*<<< orphan*/  mr_dir; int /*<<< orphan*/  mr_nents; int /*<<< orphan*/  mr_sg; struct rpcrdma_xprt* mr_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpcrdma_mr_put (int /*<<< orphan*/ *,struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xprtrdma_dma_unmap (struct rpcrdma_mr*) ; 

void
rpcrdma_mr_unmap_and_put(struct rpcrdma_mr *mr)
{
	struct rpcrdma_xprt *r_xprt = mr->mr_xprt;

	trace_xprtrdma_dma_unmap(mr);
	ib_dma_unmap_sg(r_xprt->rx_ia.ri_device,
			mr->mr_sg, mr->mr_nents, mr->mr_dir);
	__rpcrdma_mr_put(&r_xprt->rx_buf, mr);
}