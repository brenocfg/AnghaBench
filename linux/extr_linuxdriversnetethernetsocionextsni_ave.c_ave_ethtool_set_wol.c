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
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  phydev; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WAKE_ARP ; 
 int WAKE_MAGICSECURE ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int phy_ethtool_set_wol (int /*<<< orphan*/ ,struct ethtool_wolinfo*) ; 

__attribute__((used)) static int ave_ethtool_set_wol(struct net_device *ndev,
			       struct ethtool_wolinfo *wol)
{
	int ret;

	if (!ndev->phydev ||
	    (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE)))
		return -EOPNOTSUPP;

	ret = phy_ethtool_set_wol(ndev->phydev, wol);
	if (!ret)
		device_set_wakeup_enable(&ndev->dev, !!wol->wolopts);

	return ret;
}