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
struct net_device {int priv_flags; int needs_free_netdev; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  max_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int IFF_NO_QUEUE ; 
 int IFF_TX_SKB_SHARING ; 
 int IFF_UNICAST_FLT ; 
 int IFF_XMIT_DST_RELEASE ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  ipvlan_ethtool_ops ; 
 int /*<<< orphan*/  ipvlan_header_ops ; 
 int /*<<< orphan*/  ipvlan_netdev_ops ; 

void ipvlan_link_setup(struct net_device *dev)
{
	ether_setup(dev);

	dev->max_mtu = ETH_MAX_MTU;
	dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE | IFF_TX_SKB_SHARING);
	dev->priv_flags |= IFF_UNICAST_FLT | IFF_NO_QUEUE;
	dev->netdev_ops = &ipvlan_netdev_ops;
	dev->needs_free_netdev = true;
	dev->header_ops = &ipvlan_header_ops;
	dev->ethtool_ops = &ipvlan_ethtool_ops;
}