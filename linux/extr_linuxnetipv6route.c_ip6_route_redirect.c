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
struct net {int dummy; } ;
struct flowi6 {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ip6rd_flowi {struct flowi6 fl6; struct in6_addr gateway; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int /*<<< orphan*/  __ip6_route_redirect ; 
 struct dst_entry* fib6_rule_lookup (struct net*,struct flowi6*,struct sk_buff const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dst_entry *ip6_route_redirect(struct net *net,
					    const struct flowi6 *fl6,
					    const struct sk_buff *skb,
					    const struct in6_addr *gateway)
{
	int flags = RT6_LOOKUP_F_HAS_SADDR;
	struct ip6rd_flowi rdfl;

	rdfl.fl6 = *fl6;
	rdfl.gateway = *gateway;

	return fib6_rule_lookup(net, &rdfl.fl6, skb,
				flags, __ip6_route_redirect);
}