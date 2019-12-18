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
struct rt6_info {int dummy; } ;
struct net_device {int flags; } ;
struct in6_addr {int dummy; } ;
struct dst_entry {struct net_device* dev; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  __ipv6_confirm_neigh (struct net_device*,void const*) ; 
 void* choose_neigh_daddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr const*) ; 
 int /*<<< orphan*/  rt6_nexthop (struct rt6_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip6_confirm_neigh(const struct dst_entry *dst, const void *daddr)
{
	struct net_device *dev = dst->dev;
	struct rt6_info *rt = (struct rt6_info *)dst;

	daddr = choose_neigh_daddr(rt6_nexthop(rt, &in6addr_any), NULL, daddr);
	if (!daddr)
		return;
	if (dev->flags & (IFF_NOARP | IFF_LOOPBACK))
		return;
	if (ipv6_addr_is_multicast((const struct in6_addr *)daddr))
		return;
	__ipv6_confirm_neigh(dev, daddr);
}