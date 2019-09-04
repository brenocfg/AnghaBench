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
struct temac_local {scalar_t__ sdma_regs; scalar_t__ regs; int /*<<< orphan*/ * phy_node; TYPE_1__* dev; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temac_attr_group ; 
 int /*<<< orphan*/  temac_mdio_teardown (struct temac_local*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int temac_of_remove(struct platform_device *op)
{
	struct net_device *ndev = platform_get_drvdata(op);
	struct temac_local *lp = netdev_priv(ndev);

	temac_mdio_teardown(lp);
	unregister_netdev(ndev);
	sysfs_remove_group(&lp->dev->kobj, &temac_attr_group);
	of_node_put(lp->phy_node);
	lp->phy_node = NULL;
	iounmap(lp->regs);
	if (lp->sdma_regs)
		iounmap(lp->sdma_regs);
	free_netdev(ndev);
	return 0;
}