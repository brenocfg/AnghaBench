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
struct net_device {int addr_len; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_TUNNEL ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IPIP_FEATURES ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  ip_tunnel_setup (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip_net_id ; 
 int /*<<< orphan*/  ipip_netdev_ops ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void ipip_tunnel_setup(struct net_device *dev)
{
	dev->netdev_ops		= &ipip_netdev_ops;

	dev->type		= ARPHRD_TUNNEL;
	dev->flags		= IFF_NOARP;
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_LLTX;
	netif_keep_dst(dev);

	dev->features		|= IPIP_FEATURES;
	dev->hw_features	|= IPIP_FEATURES;
	ip_tunnel_setup(dev, ipip_net_id);
}