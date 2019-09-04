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
struct net_device {int dummy; } ;
struct macvlan_dev {int set_features; TYPE_1__* lowerdev; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int ALWAYS_ON_FEATURES ; 
 int MACVLAN_FEATURES ; 
 int NETIF_F_ALL_FOR_ALL ; 
 int NETIF_F_LRO ; 
 int netdev_increment_features (int,int,int) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t macvlan_fix_features(struct net_device *dev,
					      netdev_features_t features)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	netdev_features_t lowerdev_features = vlan->lowerdev->features;
	netdev_features_t mask;

	features |= NETIF_F_ALL_FOR_ALL;
	features &= (vlan->set_features | ~MACVLAN_FEATURES);
	mask = features;

	lowerdev_features &= (features | ~NETIF_F_LRO);
	features = netdev_increment_features(lowerdev_features, features, mask);
	features |= ALWAYS_ON_FEATURES;
	features &= (ALWAYS_ON_FEATURES | MACVLAN_FEATURES);

	return features;
}