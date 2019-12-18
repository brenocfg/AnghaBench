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
struct net_device {int hw_enc_features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_ALL_TSO ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_GSO_ENCAP_ALL ; 
 int NETIF_F_HW_CSUM ; 

__attribute__((used)) static inline netdev_features_t vlan_tnl_features(struct net_device *real_dev)
{
	netdev_features_t ret;

	ret = real_dev->hw_enc_features &
	      (NETIF_F_CSUM_MASK | NETIF_F_ALL_TSO | NETIF_F_GSO_ENCAP_ALL);

	if ((ret & NETIF_F_GSO_ENCAP_ALL) && (ret & NETIF_F_CSUM_MASK))
		return (ret & ~NETIF_F_CSUM_MASK) | NETIF_F_HW_CSUM;
	return 0;
}