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
struct ip_tunnel {int erspan_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  erspan_net_id ; 
 int /*<<< orphan*/  erspan_netdev_ops ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  ip_tunnel_setup (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void erspan_setup(struct net_device *dev)
{
	struct ip_tunnel *t = netdev_priv(dev);

	ether_setup(dev);
	dev->max_mtu = 0;
	dev->netdev_ops = &erspan_netdev_ops;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	ip_tunnel_setup(dev, erspan_net_id);
	t->erspan_ver = 1;
}