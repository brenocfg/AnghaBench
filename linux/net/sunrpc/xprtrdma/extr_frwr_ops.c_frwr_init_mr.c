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
struct scatterlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fr_linv_done; struct ib_mr* fr_mr; } ;
struct rpcrdma_mr {struct scatterlist* mr_sg; TYPE_1__ frwr; int /*<<< orphan*/  mr_recycle; int /*<<< orphan*/  mr_list; int /*<<< orphan*/  mr_dir; } ;
struct rpcrdma_ia {unsigned int ri_max_frwr_depth; int /*<<< orphan*/  ri_mrtype; int /*<<< orphan*/  ri_pd; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ib_mr*) ; 
 int PTR_ERR (struct ib_mr*) ; 
 int /*<<< orphan*/  frwr_mr_recycle_worker ; 
 struct ib_mr* ib_alloc_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ib_dereg_mr (struct ib_mr*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct scatterlist* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  trace_xprtrdma_frwr_alloc (struct rpcrdma_mr*,int) ; 

int frwr_init_mr(struct rpcrdma_ia *ia, struct rpcrdma_mr *mr)
{
	unsigned int depth = ia->ri_max_frwr_depth;
	struct scatterlist *sg;
	struct ib_mr *frmr;
	int rc;

	/* NB: ib_alloc_mr and device drivers typically allocate
	 *     memory with GFP_KERNEL.
	 */
	frmr = ib_alloc_mr(ia->ri_pd, ia->ri_mrtype, depth);
	if (IS_ERR(frmr))
		goto out_mr_err;

	sg = kcalloc(depth, sizeof(*sg), GFP_NOFS);
	if (!sg)
		goto out_list_err;

	mr->frwr.fr_mr = frmr;
	mr->mr_dir = DMA_NONE;
	INIT_LIST_HEAD(&mr->mr_list);
	INIT_WORK(&mr->mr_recycle, frwr_mr_recycle_worker);
	init_completion(&mr->frwr.fr_linv_done);

	sg_init_table(sg, depth);
	mr->mr_sg = sg;
	return 0;

out_mr_err:
	rc = PTR_ERR(frmr);
	trace_xprtrdma_frwr_alloc(mr, rc);
	return rc;

out_list_err:
	ib_dereg_mr(frmr);
	return -ENOMEM;
}