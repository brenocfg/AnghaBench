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
struct net_device {int ifindex; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct fib6_nh {int fib_nh_flags; struct net_device* fib_nh_dev; } ;

/* Variables and functions */
 int RT6_LOOKUP_F_IFACE ; 
 int RTNH_F_DEAD ; 
 scalar_t__ ipv6_chk_addr (struct net*,struct in6_addr const*,struct net_device const*,int) ; 

__attribute__((used)) static bool __rt6_device_match(struct net *net, const struct fib6_nh *nh,
			       const struct in6_addr *saddr, int oif, int flags)
{
	const struct net_device *dev;

	if (nh->fib_nh_flags & RTNH_F_DEAD)
		return false;

	dev = nh->fib_nh_dev;
	if (oif) {
		if (dev->ifindex == oif)
			return true;
	} else {
		if (ipv6_chk_addr(net, saddr, dev,
				  flags & RT6_LOOKUP_F_IFACE))
			return true;
	}

	return false;
}