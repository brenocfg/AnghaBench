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
struct net_device {int needs_free_netdev; int addr_len; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_TUNNEL6 ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IPXIPX_FEATURES ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_dev_free ; 
 int /*<<< orphan*/  ip6_tnl_netdev_ops ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void ip6_tnl_dev_setup(struct net_device *dev)
{
	dev->netdev_ops = &ip6_tnl_netdev_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = ip6_dev_free;

	dev->type = ARPHRD_TUNNEL6;
	dev->flags |= IFF_NOARP;
	dev->addr_len = sizeof(struct in6_addr);
	dev->features |= NETIF_F_LLTX;
	netif_keep_dst(dev);

	dev->features		|= IPXIPX_FEATURES;
	dev->hw_features	|= IPXIPX_FEATURES;

	/* This perm addr will be used as interface identifier by IPv6 */
	dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_random_addr(dev->perm_addr);
}