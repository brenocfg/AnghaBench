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
struct ipvl_dev {int /*<<< orphan*/  phy_dev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int __ethtool_get_link_ksettings (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipvlan_ethtool_get_link_ksettings(struct net_device *dev,
					     struct ethtool_link_ksettings *cmd)
{
	const struct ipvl_dev *ipvlan = netdev_priv(dev);

	return __ethtool_get_link_ksettings(ipvlan->phy_dev, cmd);
}