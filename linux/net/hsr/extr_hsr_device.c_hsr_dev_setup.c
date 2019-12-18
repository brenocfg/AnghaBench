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
struct net_device {int needs_free_netdev; int hw_features; int features; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; scalar_t__ min_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_GSO_MASK ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_NETNS_LOCAL ; 
 int NETIF_F_SG ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  hsr_device_ops ; 
 int /*<<< orphan*/  hsr_header_ops ; 
 int /*<<< orphan*/  hsr_type ; 

void hsr_dev_setup(struct net_device *dev)
{
	eth_hw_addr_random(dev);

	ether_setup(dev);
	dev->min_mtu = 0;
	dev->header_ops = &hsr_header_ops;
	dev->netdev_ops = &hsr_device_ops;
	SET_NETDEV_DEVTYPE(dev, &hsr_type);
	dev->priv_flags |= IFF_NO_QUEUE;

	dev->needs_free_netdev = true;

	dev->hw_features = NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HIGHDMA |
			   NETIF_F_GSO_MASK | NETIF_F_HW_CSUM |
			   NETIF_F_HW_VLAN_CTAG_TX;

	dev->features = dev->hw_features;

	/* Prevent recursive tx locking */
	dev->features |= NETIF_F_LLTX;
	/* VLAN on top of HSR needs testing and probably some work on
	 * hsr_header_create() etc.
	 */
	dev->features |= NETIF_F_VLAN_CHALLENGED;
	/* Not sure about this. Taken from bridge code. netdev_features.h says
	 * it means "Does not change network namespaces".
	 */
	dev->features |= NETIF_F_NETNS_LOCAL;
}