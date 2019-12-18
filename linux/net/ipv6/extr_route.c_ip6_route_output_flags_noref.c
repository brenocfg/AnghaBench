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
struct sock {scalar_t__ sk_bound_dev_if; } ;
struct net {int dummy; } ;
struct flowi6 {scalar_t__ flowi6_oif; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowi6_iif; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  srcprefs; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MULTICAST ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int RT6_LOOKUP_F_DST_NOREF ; 
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int RT6_LOOKUP_F_IFACE ; 
 struct dst_entry* fib6_rule_lookup (struct net*,struct flowi6*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* inet6_sk (struct sock const*) ; 
 int /*<<< orphan*/  ip6_pol_route_output ; 
 int ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 struct dst_entry* l3mdev_link_scope_lookup (struct net*,struct flowi6*) ; 
 scalar_t__ rt6_need_strict (int /*<<< orphan*/ *) ; 
 int rt6_srcprefs2flags (int /*<<< orphan*/ ) ; 

struct dst_entry *ip6_route_output_flags_noref(struct net *net,
					       const struct sock *sk,
					       struct flowi6 *fl6, int flags)
{
	bool any_src;

	if (ipv6_addr_type(&fl6->daddr) &
	    (IPV6_ADDR_MULTICAST | IPV6_ADDR_LINKLOCAL)) {
		struct dst_entry *dst;

		/* This function does not take refcnt on the dst */
		dst = l3mdev_link_scope_lookup(net, fl6);
		if (dst)
			return dst;
	}

	fl6->flowi6_iif = LOOPBACK_IFINDEX;

	flags |= RT6_LOOKUP_F_DST_NOREF;
	any_src = ipv6_addr_any(&fl6->saddr);
	if ((sk && sk->sk_bound_dev_if) || rt6_need_strict(&fl6->daddr) ||
	    (fl6->flowi6_oif && any_src))
		flags |= RT6_LOOKUP_F_IFACE;

	if (!any_src)
		flags |= RT6_LOOKUP_F_HAS_SADDR;
	else if (sk)
		flags |= rt6_srcprefs2flags(inet6_sk(sk)->srcprefs);

	return fib6_rule_lookup(net, fl6, NULL, flags, ip6_pol_route_output);
}