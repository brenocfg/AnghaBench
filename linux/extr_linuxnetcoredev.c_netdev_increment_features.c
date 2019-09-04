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
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_ALL_FOR_ALL ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_ONE_FOR_ALL ; 
 int NETIF_F_VLAN_CHALLENGED ; 

netdev_features_t netdev_increment_features(netdev_features_t all,
	netdev_features_t one, netdev_features_t mask)
{
	if (mask & NETIF_F_HW_CSUM)
		mask |= NETIF_F_CSUM_MASK;
	mask |= NETIF_F_VLAN_CHALLENGED;

	all |= one & (NETIF_F_ONE_FOR_ALL | NETIF_F_CSUM_MASK) & mask;
	all &= one | ~NETIF_F_ALL_FOR_ALL;

	/* If one device supports hw checksumming, set for all. */
	if (all & NETIF_F_HW_CSUM)
		all &= ~(NETIF_F_CSUM_MASK & ~NETIF_F_HW_CSUM);

	return all;
}