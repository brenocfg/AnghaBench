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
typedef  int u32 ;
struct net_device {int features; int hw_features; int wanted_features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ETH_ALL_FEATURES ; 
 int ETH_ALL_FLAGS ; 
 int ETH_FLAG_LRO ; 
 int ETH_FLAG_NTUPLE ; 
 int ETH_FLAG_RXHASH ; 
 int ETH_FLAG_RXVLAN ; 
 int ETH_FLAG_TXVLAN ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_LRO ; 
 int NETIF_F_NTUPLE ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  __netdev_update_features (struct net_device*) ; 

__attribute__((used)) static int __ethtool_set_flags(struct net_device *dev, u32 data)
{
	netdev_features_t features = 0, changed;

	if (data & ~ETH_ALL_FLAGS)
		return -EINVAL;

	if (data & ETH_FLAG_LRO)
		features |= NETIF_F_LRO;
	if (data & ETH_FLAG_RXVLAN)
		features |= NETIF_F_HW_VLAN_CTAG_RX;
	if (data & ETH_FLAG_TXVLAN)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	if (data & ETH_FLAG_NTUPLE)
		features |= NETIF_F_NTUPLE;
	if (data & ETH_FLAG_RXHASH)
		features |= NETIF_F_RXHASH;

	/* allow changing only bits set in hw_features */
	changed = (features ^ dev->features) & ETH_ALL_FEATURES;
	if (changed & ~dev->hw_features)
		return (changed & dev->hw_features) ? -EINVAL : -EOPNOTSUPP;

	dev->wanted_features =
		(dev->wanted_features & ~changed) | (features & changed);

	__netdev_update_features(dev);

	return 0;
}