#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int addr_len; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {struct iphdr iph; } ;
struct ip_tunnel {TYPE_1__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int ip_tunnel_init (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static int vti_tunnel_init(struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct iphdr *iph = &tunnel->parms.iph;

	memcpy(dev->dev_addr, &iph->saddr, 4);
	memcpy(dev->broadcast, &iph->daddr, 4);

	dev->flags		= IFF_NOARP;
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_LLTX;
	netif_keep_dst(dev);

	return ip_tunnel_init(dev);
}