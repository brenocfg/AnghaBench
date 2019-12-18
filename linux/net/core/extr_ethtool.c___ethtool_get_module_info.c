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
struct phy_device {TYPE_1__* drv; } ;
struct net_device {scalar_t__ sfp_bus; struct phy_device* phydev; struct ethtool_ops* ethtool_ops; } ;
struct ethtool_ops {int (* get_module_info ) (struct net_device*,struct ethtool_modinfo*) ;} ;
struct ethtool_modinfo {int dummy; } ;
struct TYPE_2__ {int (* module_info ) (struct phy_device*,struct ethtool_modinfo*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int sfp_get_module_info (scalar_t__,struct ethtool_modinfo*) ; 
 int stub1 (struct phy_device*,struct ethtool_modinfo*) ; 
 int stub2 (struct net_device*,struct ethtool_modinfo*) ; 

__attribute__((used)) static int __ethtool_get_module_info(struct net_device *dev,
				     struct ethtool_modinfo *modinfo)
{
	const struct ethtool_ops *ops = dev->ethtool_ops;
	struct phy_device *phydev = dev->phydev;

	if (dev->sfp_bus)
		return sfp_get_module_info(dev->sfp_bus, modinfo);

	if (phydev && phydev->drv && phydev->drv->module_info)
		return phydev->drv->module_info(phydev, modinfo);

	if (ops->get_module_info)
		return ops->get_module_info(dev, modinfo);

	return -EOPNOTSUPP;
}