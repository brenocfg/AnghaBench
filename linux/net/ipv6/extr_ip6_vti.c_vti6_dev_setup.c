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
struct net_device {int needs_free_netdev; int addr_len; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  flags; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  type; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct ipv6hdr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_TUNNEL6 ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IPV4_MIN_MTU ; 
 scalar_t__ IP_MAX_MTU ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 
 int /*<<< orphan*/  vti6_dev_free ; 
 int /*<<< orphan*/  vti6_netdev_ops ; 

__attribute__((used)) static void vti6_dev_setup(struct net_device *dev)
{
	dev->netdev_ops = &vti6_netdev_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = vti6_dev_free;

	dev->type = ARPHRD_TUNNEL6;
	dev->min_mtu = IPV4_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - sizeof(struct ipv6hdr);
	dev->flags |= IFF_NOARP;
	dev->addr_len = sizeof(struct in6_addr);
	netif_keep_dst(dev);
	/* This perm addr will be used as interface identifier by IPv6 */
	dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_random_addr(dev->perm_addr);
}