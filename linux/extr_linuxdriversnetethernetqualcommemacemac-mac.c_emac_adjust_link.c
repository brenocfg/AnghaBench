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
struct phy_device {scalar_t__ link; } ;
struct net_device {struct phy_device* phydev; } ;
struct emac_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_mac_start (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_stop (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_link_change (struct emac_adapter*,int) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void emac_adjust_link(struct net_device *netdev)
{
	struct emac_adapter *adpt = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;

	if (phydev->link) {
		emac_mac_start(adpt);
		emac_sgmii_link_change(adpt, true);
	} else {
		emac_sgmii_link_change(adpt, false);
		emac_mac_stop(adpt);
	}

	phy_print_status(phydev);
}