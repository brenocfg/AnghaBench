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
struct net_device {int needs_free_netdev; int addr_len; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; scalar_t__ mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct iphdr {int dummy; } ;
struct ip_tunnel {int hlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_SIT ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 scalar_t__ IP6_MAX_MTU ; 
 int /*<<< orphan*/  IPV6_MIN_MTU ; 
 scalar_t__ LL_MAX_HEADER ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  SIT_FEATURES ; 
 int /*<<< orphan*/  ipip6_dev_free ; 
 int /*<<< orphan*/  ipip6_netdev_ops ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void ipip6_tunnel_setup(struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	int t_hlen = tunnel->hlen + sizeof(struct iphdr);

	dev->netdev_ops		= &ipip6_netdev_ops;
	dev->needs_free_netdev	= true;
	dev->priv_destructor	= ipip6_dev_free;

	dev->type		= ARPHRD_SIT;
	dev->hard_header_len	= LL_MAX_HEADER + t_hlen;
	dev->mtu		= ETH_DATA_LEN - t_hlen;
	dev->min_mtu		= IPV6_MIN_MTU;
	dev->max_mtu		= IP6_MAX_MTU - t_hlen;
	dev->flags		= IFF_NOARP;
	netif_keep_dst(dev);
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_LLTX;
	dev->features		|= SIT_FEATURES;
	dev->hw_features	|= SIT_FEATURES;
}