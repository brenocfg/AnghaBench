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
struct TYPE_6__ {int /*<<< orphan*/  rb_mrlock; } ;
struct TYPE_5__ {int /*<<< orphan*/  ri_device; } ;
struct TYPE_4__ {int /*<<< orphan*/  mrs_orphaned; int /*<<< orphan*/  mrs_recovered; } ;
struct rpcrdma_xprt {TYPE_3__ rx_buf; TYPE_2__ rx_ia; TYPE_1__ rx_stats; } ;
struct rpcrdma_mr {int /*<<< orphan*/  mr_all; int /*<<< orphan*/  mr_dir; int /*<<< orphan*/  mr_nents; int /*<<< orphan*/  mr_sg; struct rpcrdma_xprt* mr_xprt; } ;

/* Variables and functions */
 int __fmr_unmap (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  fmr_op_release_mr (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  rpcrdma_mr_unmap_and_put (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_dma_unmap (struct rpcrdma_mr*) ; 

__attribute__((used)) static void
fmr_op_recover_mr(struct rpcrdma_mr *mr)
{
	struct rpcrdma_xprt *r_xprt = mr->mr_xprt;
	int rc;

	/* ORDER: invalidate first */
	rc = __fmr_unmap(mr);
	if (rc)
		goto out_release;

	/* ORDER: then DMA unmap */
	rpcrdma_mr_unmap_and_put(mr);

	r_xprt->rx_stats.mrs_recovered++;
	return;

out_release:
	pr_err("rpcrdma: FMR reset failed (%d), %p released\n", rc, mr);
	r_xprt->rx_stats.mrs_orphaned++;

	trace_xprtrdma_dma_unmap(mr);
	ib_dma_unmap_sg(r_xprt->rx_ia.ri_device,
			mr->mr_sg, mr->mr_nents, mr->mr_dir);

	spin_lock(&r_xprt->rx_buf.rb_mrlock);
	list_del(&mr->mr_all);
	spin_unlock(&r_xprt->rx_buf.rb_mrlock);

	fmr_op_release_mr(mr);
}