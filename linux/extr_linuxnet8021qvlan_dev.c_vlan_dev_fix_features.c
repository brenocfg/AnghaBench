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
struct net_device {int vlan_features; int features; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {struct net_device* real_dev; } ;

/* Variables and functions */
 int NETIF_F_GSO_SOFTWARE ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SOFT_FEATURES ; 
 int netdev_intersect_features (int,int) ; 
 TYPE_1__* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t vlan_dev_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	netdev_features_t old_features = features;
	netdev_features_t lower_features;

	lower_features = netdev_intersect_features((real_dev->vlan_features |
						    NETIF_F_RXCSUM),
						   real_dev->features);

	/* Add HW_CSUM setting to preserve user ability to control
	 * checksum offload on the vlan device.
	 */
	if (lower_features & (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM))
		lower_features |= NETIF_F_HW_CSUM;
	features = netdev_intersect_features(features, lower_features);
	features |= old_features & (NETIF_F_SOFT_FEATURES | NETIF_F_GSO_SOFTWARE);
	features |= NETIF_F_LLTX;

	return features;
}