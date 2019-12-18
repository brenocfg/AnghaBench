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
struct rt6_info {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int flowi6_oif; int /*<<< orphan*/  saddr; struct in6_addr const daddr; } ;
struct dst_entry {scalar_t__ error; } ;

/* Variables and functions */
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int RT6_LOOKUP_F_IFACE ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* fib6_rule_lookup (struct net*,struct flowi6*,struct sk_buff const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_pol_route_lookup ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in6_addr const*,int) ; 

struct rt6_info *rt6_lookup(struct net *net, const struct in6_addr *daddr,
			    const struct in6_addr *saddr, int oif,
			    const struct sk_buff *skb, int strict)
{
	struct flowi6 fl6 = {
		.flowi6_oif = oif,
		.daddr = *daddr,
	};
	struct dst_entry *dst;
	int flags = strict ? RT6_LOOKUP_F_IFACE : 0;

	if (saddr) {
		memcpy(&fl6.saddr, saddr, sizeof(*saddr));
		flags |= RT6_LOOKUP_F_HAS_SADDR;
	}

	dst = fib6_rule_lookup(net, &fl6, skb, flags, ip6_pol_route_lookup);
	if (dst->error == 0)
		return (struct rt6_info *) dst;

	dst_release(dst);

	return NULL;
}