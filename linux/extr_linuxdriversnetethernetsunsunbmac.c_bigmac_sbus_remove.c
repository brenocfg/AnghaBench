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
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/ * resource; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct bigmac {int /*<<< orphan*/  bblock_dvma; int /*<<< orphan*/  bmac_block; int /*<<< orphan*/  tregs; int /*<<< orphan*/  bregs; int /*<<< orphan*/  creg; int /*<<< orphan*/  gregs; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_REG_SIZE ; 
 int /*<<< orphan*/  CREG_REG_SIZE ; 
 int /*<<< orphan*/  GLOB_REG_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TCVR_REG_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bigmac* platform_get_drvdata (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int bigmac_sbus_remove(struct platform_device *op)
{
	struct bigmac *bp = platform_get_drvdata(op);
	struct device *parent = op->dev.parent;
	struct net_device *net_dev = bp->dev;
	struct platform_device *qec_op;

	qec_op = to_platform_device(parent);

	unregister_netdev(net_dev);

	of_iounmap(&qec_op->resource[0], bp->gregs, GLOB_REG_SIZE);
	of_iounmap(&op->resource[0], bp->creg, CREG_REG_SIZE);
	of_iounmap(&op->resource[1], bp->bregs, BMAC_REG_SIZE);
	of_iounmap(&op->resource[2], bp->tregs, TCVR_REG_SIZE);
	dma_free_coherent(&op->dev,
			  PAGE_SIZE,
			  bp->bmac_block,
			  bp->bblock_dvma);

	free_netdev(net_dev);

	return 0;
}