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
struct net_device {int needs_free_netdev; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  features; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; scalar_t__ max_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  ip6gre_dev_free ; 
 int /*<<< orphan*/  ip6gre_tap_netdev_ops ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void ip6gre_tap_setup(struct net_device *dev)
{

	ether_setup(dev);

	dev->max_mtu = 0;
	dev->netdev_ops = &ip6gre_tap_netdev_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = ip6gre_dev_free;

	dev->features |= NETIF_F_NETNS_LOCAL;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netif_keep_dst(dev);
}