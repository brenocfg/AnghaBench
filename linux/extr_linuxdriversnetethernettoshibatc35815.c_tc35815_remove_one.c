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
struct tc35815_local {int /*<<< orphan*/  mii_bus; } ;
struct pci_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void tc35815_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct tc35815_local *lp = netdev_priv(dev);

	phy_disconnect(dev->phydev);
	mdiobus_unregister(lp->mii_bus);
	mdiobus_free(lp->mii_bus);
	unregister_netdev(dev);
	free_netdev(dev);
}