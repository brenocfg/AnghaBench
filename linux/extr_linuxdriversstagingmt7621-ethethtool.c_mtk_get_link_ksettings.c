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
struct net_device {int dummy; } ;
struct mtk_mac {scalar_t__ phy_flags; int /*<<< orphan*/  phy_dev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MTK_PHY_FLAG_ATTACH ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 int phy_read_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_get_link_ksettings(struct net_device *dev,
				  struct ethtool_link_ksettings *cmd)
{
	struct mtk_mac *mac = netdev_priv(dev);
	int err;

	if (!mac->phy_dev)
		return -ENODEV;

	if (mac->phy_flags == MTK_PHY_FLAG_ATTACH) {
		err = phy_read_status(mac->phy_dev);
		if (err)
			return -ENODEV;
	}

	phy_ethtool_ksettings_get(mac->phy_dev, cmd);
	return 0;
}