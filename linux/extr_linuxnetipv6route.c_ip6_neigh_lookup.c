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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct neighbour {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct neighbour*) ; 
 struct neighbour* __ipv6_neigh_lookup (struct net_device*,void const*) ; 
 void* choose_neigh_daddr (struct in6_addr const*,struct sk_buff*,void const*) ; 
 int /*<<< orphan*/  nd_tbl ; 
 struct neighbour* neigh_create (int /*<<< orphan*/ *,void const*,struct net_device*) ; 

struct neighbour *ip6_neigh_lookup(const struct in6_addr *gw,
				   struct net_device *dev,
				   struct sk_buff *skb,
				   const void *daddr)
{
	struct neighbour *n;

	daddr = choose_neigh_daddr(gw, skb, daddr);
	n = __ipv6_neigh_lookup(dev, daddr);
	if (n)
		return n;

	n = neigh_create(&nd_tbl, daddr, dev);
	return IS_ERR(n) ? NULL : n;
}