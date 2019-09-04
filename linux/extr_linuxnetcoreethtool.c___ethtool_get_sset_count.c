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
struct net_device {scalar_t__ phydev; struct ethtool_ops* ethtool_ops; } ;
struct ethtool_ops {int (* get_sset_count ) (struct net_device*,int) ;scalar_t__ get_strings; int /*<<< orphan*/  get_ethtool_phy_stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int ETH_SS_FEATURES ; 
 int ETH_SS_PHY_STATS ; 
 int ETH_SS_PHY_TUNABLES ; 
 int ETH_SS_RSS_HASH_FUNCS ; 
 int ETH_SS_TUNABLES ; 
 int /*<<< orphan*/  netdev_features_strings ; 
 int phy_ethtool_get_sset_count (scalar_t__) ; 
 int /*<<< orphan*/  phy_tunable_strings ; 
 int /*<<< orphan*/  rss_hash_func_strings ; 
 int stub1 (struct net_device*,int) ; 
 int /*<<< orphan*/  tunable_strings ; 

__attribute__((used)) static int __ethtool_get_sset_count(struct net_device *dev, int sset)
{
	const struct ethtool_ops *ops = dev->ethtool_ops;

	if (sset == ETH_SS_FEATURES)
		return ARRAY_SIZE(netdev_features_strings);

	if (sset == ETH_SS_RSS_HASH_FUNCS)
		return ARRAY_SIZE(rss_hash_func_strings);

	if (sset == ETH_SS_TUNABLES)
		return ARRAY_SIZE(tunable_strings);

	if (sset == ETH_SS_PHY_TUNABLES)
		return ARRAY_SIZE(phy_tunable_strings);

	if (sset == ETH_SS_PHY_STATS && dev->phydev &&
	    !ops->get_ethtool_phy_stats)
		return phy_ethtool_get_sset_count(dev->phydev);

	if (ops->get_sset_count && ops->get_strings)
		return ops->get_sset_count(dev, sset);
	else
		return -EOPNOTSUPP;
}