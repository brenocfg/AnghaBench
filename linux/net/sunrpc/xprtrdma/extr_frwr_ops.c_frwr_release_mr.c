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
struct TYPE_2__ {int /*<<< orphan*/  fr_mr; } ;
struct rpcrdma_mr {struct rpcrdma_mr* mr_sg; TYPE_1__ frwr; } ;

/* Variables and functions */
 int ib_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  trace_xprtrdma_frwr_dereg (struct rpcrdma_mr*,int) ; 

void frwr_release_mr(struct rpcrdma_mr *mr)
{
	int rc;

	rc = ib_dereg_mr(mr->frwr.fr_mr);
	if (rc)
		trace_xprtrdma_frwr_dereg(mr, rc);
	kfree(mr->mr_sg);
	kfree(mr);
}