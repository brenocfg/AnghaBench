#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ri_id; } ;
struct rpcrdma_xprt {TYPE_3__ rx_ia; } ;
struct rpcrdma_mr {scalar_t__ mr_dir; TYPE_1__* mr_req; int /*<<< orphan*/  mr_nents; int /*<<< orphan*/  mr_sg; struct rpcrdma_xprt* mr_xprt; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  rl_free_mrs; } ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rpcrdma_mr_push (struct rpcrdma_mr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_mr_unmap (struct rpcrdma_mr*) ; 

void rpcrdma_mr_put(struct rpcrdma_mr *mr)
{
	struct rpcrdma_xprt *r_xprt = mr->mr_xprt;

	if (mr->mr_dir != DMA_NONE) {
		trace_xprtrdma_mr_unmap(mr);
		ib_dma_unmap_sg(r_xprt->rx_ia.ri_id->device,
				mr->mr_sg, mr->mr_nents, mr->mr_dir);
		mr->mr_dir = DMA_NONE;
	}

	rpcrdma_mr_push(mr, &mr->mr_req->rl_free_mrs);
}