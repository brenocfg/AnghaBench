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
struct TYPE_5__ {int /*<<< orphan*/  mrs_orphaned; int /*<<< orphan*/  mrs_recovered; } ;
struct rpcrdma_ia {int /*<<< orphan*/  ri_device; } ;
struct rpcrdma_xprt {TYPE_3__ rx_buf; TYPE_2__ rx_stats; struct rpcrdma_ia rx_ia; } ;
struct TYPE_4__ {int fr_state; } ;
struct rpcrdma_mr {int /*<<< orphan*/  mr_all; int /*<<< orphan*/  mr_dir; int /*<<< orphan*/  mr_nents; int /*<<< orphan*/  mr_sg; struct rpcrdma_xprt* mr_xprt; TYPE_1__ frwr; } ;
typedef  enum rpcrdma_frwr_state { ____Placeholder_rpcrdma_frwr_state } rpcrdma_frwr_state ;

/* Variables and functions */
 int FRWR_FLUSHED_LI ; 
 int __frwr_mr_reset (struct rpcrdma_ia*,struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  frwr_op_release_mr (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  rpcrdma_mr_put (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_dma_unmap (struct rpcrdma_mr*) ; 

__attribute__((used)) static void
frwr_op_recover_mr(struct rpcrdma_mr *mr)
{
	enum rpcrdma_frwr_state state = mr->frwr.fr_state;
	struct rpcrdma_xprt *r_xprt = mr->mr_xprt;
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	int rc;

	rc = __frwr_mr_reset(ia, mr);
	if (state != FRWR_FLUSHED_LI) {
		trace_xprtrdma_dma_unmap(mr);
		ib_dma_unmap_sg(ia->ri_device,
				mr->mr_sg, mr->mr_nents, mr->mr_dir);
	}
	if (rc)
		goto out_release;

	rpcrdma_mr_put(mr);
	r_xprt->rx_stats.mrs_recovered++;
	return;

out_release:
	pr_err("rpcrdma: FRWR reset failed %d, %p released\n", rc, mr);
	r_xprt->rx_stats.mrs_orphaned++;

	spin_lock(&r_xprt->rx_buf.rb_mrlock);
	list_del(&mr->mr_all);
	spin_unlock(&r_xprt->rx_buf.rb_mrlock);

	frwr_op_release_mr(mr);
}