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
typedef  int /*<<< orphan*/  u32 ;
struct rt6_info {int dummy; } ;
struct TYPE_2__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  saddr; struct in6_addr const daddr; int /*<<< orphan*/  flowi6_oif; } ;
struct fib6_table {int dummy; } ;
struct fib6_config {int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_prefsrc; } ;

/* Variables and functions */
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int RT6_LOOKUP_F_IGNORE_LINKSTATE ; 
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 struct rt6_info* ip6_pol_route (struct net*,struct fib6_table*,int /*<<< orphan*/ ,struct flowi6*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rt6_info *ip6_nh_lookup_table(struct net *net,
					    struct fib6_config *cfg,
					    const struct in6_addr *gw_addr,
					    u32 tbid, int flags)
{
	struct flowi6 fl6 = {
		.flowi6_oif = cfg->fc_ifindex,
		.daddr = *gw_addr,
		.saddr = cfg->fc_prefsrc,
	};
	struct fib6_table *table;
	struct rt6_info *rt;

	table = fib6_get_table(net, tbid);
	if (!table)
		return NULL;

	if (!ipv6_addr_any(&cfg->fc_prefsrc))
		flags |= RT6_LOOKUP_F_HAS_SADDR;

	flags |= RT6_LOOKUP_F_IGNORE_LINKSTATE;
	rt = ip6_pol_route(net, table, cfg->fc_ifindex, &fl6, NULL, flags);

	/* if table lookup failed, fall back to full lookup */
	if (rt == net->ipv6.ip6_null_entry) {
		ip6_rt_put(rt);
		rt = NULL;
	}

	return rt;
}