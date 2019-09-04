#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int ifindex; } ;
struct TYPE_4__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_2__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct TYPE_3__ {int nh_flags; struct net_device* nh_dev; } ;
struct fib6_info {TYPE_1__ fib6_nh; int /*<<< orphan*/  fib6_next; } ;

/* Variables and functions */
 int RT6_LOOKUP_F_IFACE ; 
 int RTNH_F_DEAD ; 
 scalar_t__ ipv6_addr_any (struct in6_addr const*) ; 
 scalar_t__ ipv6_chk_addr (struct net*,struct in6_addr const*,struct net_device const*,int) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fib6_info *rt6_device_match(struct net *net,
						 struct fib6_info *rt,
						    const struct in6_addr *saddr,
						    int oif,
						    int flags)
{
	struct fib6_info *sprt;

	if (!oif && ipv6_addr_any(saddr) &&
	    !(rt->fib6_nh.nh_flags & RTNH_F_DEAD))
		return rt;

	for (sprt = rt; sprt; sprt = rcu_dereference(sprt->fib6_next)) {
		const struct net_device *dev = sprt->fib6_nh.nh_dev;

		if (sprt->fib6_nh.nh_flags & RTNH_F_DEAD)
			continue;

		if (oif) {
			if (dev->ifindex == oif)
				return sprt;
		} else {
			if (ipv6_chk_addr(net, saddr, dev,
					  flags & RT6_LOOKUP_F_IFACE))
				return sprt;
		}
	}

	if (oif && flags & RT6_LOOKUP_F_IFACE)
		return net->ipv6.fib6_null_entry;

	return rt->fib6_nh.nh_flags & RTNH_F_DEAD ? net->ipv6.fib6_null_entry : rt;
}