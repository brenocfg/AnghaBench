#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpcrdma_ia {TYPE_3__* ri_device; int /*<<< orphan*/ * ri_ops; TYPE_1__* ri_pd; TYPE_1__* ri_id; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_3__* device; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
#define  RPCRDMA_FRWR 129 
#define  RPCRDMA_MTHCAFMR 128 
 int /*<<< orphan*/  fmr_is_supported (struct rpcrdma_ia*) ; 
 int /*<<< orphan*/  frwr_is_supported (struct rpcrdma_ia*) ; 
 TYPE_1__* ib_alloc_pd (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 TYPE_1__* rpcrdma_create_id (struct rpcrdma_xprt*,struct rpcrdma_ia*) ; 
 int /*<<< orphan*/  rpcrdma_fmr_memreg_ops ; 
 int /*<<< orphan*/  rpcrdma_frwr_memreg_ops ; 
 int /*<<< orphan*/  rpcrdma_ia_close (struct rpcrdma_ia*) ; 
 int xprt_rdma_memreg_strategy ; 

int
rpcrdma_ia_open(struct rpcrdma_xprt *xprt)
{
	struct rpcrdma_ia *ia = &xprt->rx_ia;
	int rc;

	ia->ri_id = rpcrdma_create_id(xprt, ia);
	if (IS_ERR(ia->ri_id)) {
		rc = PTR_ERR(ia->ri_id);
		goto out_err;
	}
	ia->ri_device = ia->ri_id->device;

	ia->ri_pd = ib_alloc_pd(ia->ri_device, 0);
	if (IS_ERR(ia->ri_pd)) {
		rc = PTR_ERR(ia->ri_pd);
		pr_err("rpcrdma: ib_alloc_pd() returned %d\n", rc);
		goto out_err;
	}

	switch (xprt_rdma_memreg_strategy) {
	case RPCRDMA_FRWR:
		if (frwr_is_supported(ia)) {
			ia->ri_ops = &rpcrdma_frwr_memreg_ops;
			break;
		}
		/*FALLTHROUGH*/
	case RPCRDMA_MTHCAFMR:
		if (fmr_is_supported(ia)) {
			ia->ri_ops = &rpcrdma_fmr_memreg_ops;
			break;
		}
		/*FALLTHROUGH*/
	default:
		pr_err("rpcrdma: Device %s does not support memreg mode %d\n",
		       ia->ri_device->name, xprt_rdma_memreg_strategy);
		rc = -EINVAL;
		goto out_err;
	}

	return 0;

out_err:
	rpcrdma_ia_close(ia);
	return rc;
}