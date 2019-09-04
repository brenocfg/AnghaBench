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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mtk_mac {scalar_t__ phy_flags; TYPE_1__* phy_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ MTK_PHY_FLAG_ATTACH ; 
 int /*<<< orphan*/  ethtool_op_get_link (struct net_device*) ; 
 int genphy_update_link (TYPE_1__*) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 mtk_get_link(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	int err;

	if (!mac->phy_dev)
		goto out_get_link;

	if (mac->phy_flags == MTK_PHY_FLAG_ATTACH) {
		err = genphy_update_link(mac->phy_dev);
		if (err)
			goto out_get_link;
	}

	return mac->phy_dev->link;

out_get_link:
	return ethtool_op_get_link(dev);
}