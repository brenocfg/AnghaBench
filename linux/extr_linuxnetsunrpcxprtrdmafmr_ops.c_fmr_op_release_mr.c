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
struct TYPE_2__ {int /*<<< orphan*/  fm_mr; struct rpcrdma_mr* fm_physaddrs; } ;
struct rpcrdma_mr {TYPE_1__ fmr; struct rpcrdma_mr* mr_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int __fmr_unmap (struct rpcrdma_mr*) ; 
 int ib_dealloc_fmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  pr_err (char*,struct rpcrdma_mr*,int) ; 
 int /*<<< orphan*/  unmap_list ; 

__attribute__((used)) static void
fmr_op_release_mr(struct rpcrdma_mr *mr)
{
	LIST_HEAD(unmap_list);
	int rc;

	kfree(mr->fmr.fm_physaddrs);
	kfree(mr->mr_sg);

	/* In case this one was left mapped, try to unmap it
	 * to prevent dealloc_fmr from failing with EBUSY
	 */
	rc = __fmr_unmap(mr);
	if (rc)
		pr_err("rpcrdma: final ib_unmap_fmr for %p failed %i\n",
		       mr, rc);

	rc = ib_dealloc_fmr(mr->fmr.fm_mr);
	if (rc)
		pr_err("rpcrdma: final ib_dealloc_fmr for %p returned %i\n",
		       mr, rc);

	kfree(mr);
}