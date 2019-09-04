#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mtk_mac {TYPE_5__* phy_dev; int /*<<< orphan*/  phy_flags; TYPE_3__* hw; } ;
struct TYPE_10__ {size_t phy_address; } ;
struct ethtool_link_ksettings {TYPE_4__ base; } ;
struct TYPE_7__ {size_t addr; } ;
struct TYPE_11__ {TYPE_1__ mdio; } ;
struct TYPE_9__ {scalar_t__ mii_bus; TYPE_2__* phy; } ;
struct TYPE_8__ {TYPE_5__** phy; scalar_t__* phy_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MTK_PHY_FLAG_ATTACH ; 
 int /*<<< orphan*/  MTK_PHY_FLAG_PORT ; 
 TYPE_5__* mdiobus_get_phy (scalar_t__,size_t) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int phy_ethtool_ksettings_set (TYPE_5__*,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int mtk_set_link_ksettings(struct net_device *dev,
				  const struct ethtool_link_ksettings *cmd)
{
	struct mtk_mac *mac = netdev_priv(dev);

	if (!mac->phy_dev)
		return -ENODEV;

	if (cmd->base.phy_address != mac->phy_dev->mdio.addr) {
		if (mac->hw->phy->phy_node[cmd->base.phy_address]) {
			mac->phy_dev = mac->hw->phy->phy[cmd->base.phy_address];
			mac->phy_flags = MTK_PHY_FLAG_PORT;
		} else if (mac->hw->mii_bus) {
			mac->phy_dev = mdiobus_get_phy(mac->hw->mii_bus,
						       cmd->base.phy_address);
			if (!mac->phy_dev)
				return -ENODEV;
			mac->phy_flags = MTK_PHY_FLAG_ATTACH;
		} else {
			return -ENODEV;
		}
	}

	return phy_ethtool_ksettings_set(mac->phy_dev, cmd);
}