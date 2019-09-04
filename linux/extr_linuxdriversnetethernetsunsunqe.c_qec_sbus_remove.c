#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sunqe_buffers {int dummy; } ;
struct sunqe {int /*<<< orphan*/  buffers_dvma; int /*<<< orphan*/  buffers; int /*<<< orphan*/  qblock_dvma; int /*<<< orphan*/  qe_block; int /*<<< orphan*/  mregs; int /*<<< orphan*/  qcregs; struct net_device* dev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREG_REG_SIZE ; 
 int /*<<< orphan*/  MREGS_REG_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sunqe* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int qec_sbus_remove(struct platform_device *op)
{
	struct sunqe *qp = platform_get_drvdata(op);
	struct net_device *net_dev = qp->dev;

	unregister_netdev(net_dev);

	of_iounmap(&op->resource[0], qp->qcregs, CREG_REG_SIZE);
	of_iounmap(&op->resource[1], qp->mregs, MREGS_REG_SIZE);
	dma_free_coherent(&op->dev, PAGE_SIZE,
			  qp->qe_block, qp->qblock_dvma);
	dma_free_coherent(&op->dev, sizeof(struct sunqe_buffers),
			  qp->buffers, qp->buffers_dvma);

	free_netdev(net_dev);

	return 0;
}