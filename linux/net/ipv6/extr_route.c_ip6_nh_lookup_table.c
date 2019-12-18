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
struct TYPE_2__ {scalar_t__ fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {scalar_t__ flowi6_oif; int /*<<< orphan*/  saddr; struct in6_addr const daddr; } ;
struct fib6_table {int dummy; } ;
struct fib6_result {scalar_t__ f6i; } ;
struct fib6_config {scalar_t__ fc_ifindex; int /*<<< orphan*/  fc_prefsrc; } ;

/* Variables and functions */
 int EINVAL ; 
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int RT6_LOOKUP_F_IGNORE_LINKSTATE ; 
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_select_path (struct net*,struct fib6_result*,struct flowi6*,scalar_t__,int,int /*<<< orphan*/ *,int) ; 
 int fib6_table_lookup (struct net*,struct fib6_table*,scalar_t__,struct flowi6*,struct fib6_result*,int) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip6_nh_lookup_table(struct net *net, struct fib6_config *cfg,
			       const struct in6_addr *gw_addr, u32 tbid,
			       int flags, struct fib6_result *res)
{
	struct flowi6 fl6 = {
		.flowi6_oif = cfg->fc_ifindex,
		.daddr = *gw_addr,
		.saddr = cfg->fc_prefsrc,
	};
	struct fib6_table *table;
	int err;

	table = fib6_get_table(net, tbid);
	if (!table)
		return -EINVAL;

	if (!ipv6_addr_any(&cfg->fc_prefsrc))
		flags |= RT6_LOOKUP_F_HAS_SADDR;

	flags |= RT6_LOOKUP_F_IGNORE_LINKSTATE;

	err = fib6_table_lookup(net, table, cfg->fc_ifindex, &fl6, res, flags);
	if (!err && res->f6i != net->ipv6.fib6_null_entry)
		fib6_select_path(net, res, &fl6, cfg->fc_ifindex,
				 cfg->fc_ifindex != 0, NULL, flags);

	return err;
}