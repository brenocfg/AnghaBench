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
struct net_device {int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * netdev_ops; scalar_t__ max_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  gre_tap_net_id ; 
 int /*<<< orphan*/  gre_tap_netdev_ops ; 
 int /*<<< orphan*/  ip_tunnel_setup (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipgre_tap_setup(struct net_device *dev)
{
	ether_setup(dev);
	dev->max_mtu = 0;
	dev->netdev_ops	= &gre_tap_netdev_ops;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags	|= IFF_LIVE_ADDR_CHANGE;
	ip_tunnel_setup(dev, gre_tap_net_id);
}