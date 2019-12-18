#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vlan_dev_priv {TYPE_2__* real_dev; } ;
struct phy_device {TYPE_1__* drv; } ;
struct net_device {int dummy; } ;
struct ethtool_ts_info {int so_timestamping; int phc_index; } ;
struct ethtool_ops {int (* get_ts_info ) (TYPE_2__*,struct ethtool_ts_info*) ;} ;
struct TYPE_4__ {struct phy_device* phydev; struct ethtool_ops* ethtool_ops; } ;
struct TYPE_3__ {int (* ts_info ) (struct phy_device*,struct ethtool_ts_info*) ;} ;

/* Variables and functions */
 int SOF_TIMESTAMPING_RX_SOFTWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 int stub1 (struct phy_device*,struct ethtool_ts_info*) ; 
 int stub2 (TYPE_2__*,struct ethtool_ts_info*) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static int vlan_ethtool_get_ts_info(struct net_device *dev,
				    struct ethtool_ts_info *info)
{
	const struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	const struct ethtool_ops *ops = vlan->real_dev->ethtool_ops;
	struct phy_device *phydev = vlan->real_dev->phydev;

	if (phydev && phydev->drv && phydev->drv->ts_info) {
		 return phydev->drv->ts_info(phydev, info);
	} else if (ops->get_ts_info) {
		return ops->get_ts_info(vlan->real_dev, info);
	} else {
		info->so_timestamping = SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		info->phc_index = -1;
	}

	return 0;
}