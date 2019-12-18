#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpcrdma_ia {TYPE_1__* ri_pd; TYPE_1__* ri_id; } ;
struct TYPE_5__ {scalar_t__ qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  ib_dealloc_pd (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (TYPE_1__*) ; 

void
rpcrdma_ia_close(struct rpcrdma_ia *ia)
{
	if (ia->ri_id != NULL && !IS_ERR(ia->ri_id)) {
		if (ia->ri_id->qp)
			rdma_destroy_qp(ia->ri_id);
		rdma_destroy_id(ia->ri_id);
	}
	ia->ri_id = NULL;

	/* If the pd is still busy, xprtrdma missed freeing a resource */
	if (ia->ri_pd && !IS_ERR(ia->ri_pd))
		ib_dealloc_pd(ia->ri_pd);
	ia->ri_pd = NULL;
}