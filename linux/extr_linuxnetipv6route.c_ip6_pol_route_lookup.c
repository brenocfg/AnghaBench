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
struct sk_buff {int dummy; } ;
struct rt6_info {int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {struct rt6_info* ip6_null_entry; struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi6 {int flowi6_flags; scalar_t__ flowi6_oif; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct fib6_table {int /*<<< orphan*/  tb6_root; } ;
struct fib6_node {int /*<<< orphan*/  leaf; } ;
struct fib6_info {scalar_t__ fib6_nsiblings; } ;

/* Variables and functions */
 int FLOWI_FLAG_SKIP_NH_OIF ; 
 int RT6_LOOKUP_F_IFACE ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_use_noref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fib6_node* fib6_backtrack (struct fib6_node*,int /*<<< orphan*/ *) ; 
 struct fib6_info* fib6_multipath_select (struct net*,struct fib6_info*,struct flowi6*,scalar_t__,struct sk_buff const*,int) ; 
 struct fib6_node* fib6_node_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rt6_info* ip6_create_rt_rcu (struct fib6_info*) ; 
 scalar_t__ ip6_hold_safe (struct net*,struct rt6_info**,int) ; 
 int /*<<< orphan*/  jiffies ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct fib6_info* rt6_device_match (struct net*,struct fib6_info*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct rt6_info* rt6_find_cached_rt (struct fib6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fib6_table_lookup (struct net*,struct fib6_info*,struct fib6_table*,struct flowi6*) ; 

__attribute__((used)) static struct rt6_info *ip6_pol_route_lookup(struct net *net,
					     struct fib6_table *table,
					     struct flowi6 *fl6,
					     const struct sk_buff *skb,
					     int flags)
{
	struct fib6_info *f6i;
	struct fib6_node *fn;
	struct rt6_info *rt;

	if (fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF)
		flags &= ~RT6_LOOKUP_F_IFACE;

	rcu_read_lock();
	fn = fib6_node_lookup(&table->tb6_root, &fl6->daddr, &fl6->saddr);
restart:
	f6i = rcu_dereference(fn->leaf);
	if (!f6i) {
		f6i = net->ipv6.fib6_null_entry;
	} else {
		f6i = rt6_device_match(net, f6i, &fl6->saddr,
				      fl6->flowi6_oif, flags);
		if (f6i->fib6_nsiblings && fl6->flowi6_oif == 0)
			f6i = fib6_multipath_select(net, f6i, fl6,
						    fl6->flowi6_oif, skb,
						    flags);
	}
	if (f6i == net->ipv6.fib6_null_entry) {
		fn = fib6_backtrack(fn, &fl6->saddr);
		if (fn)
			goto restart;
	}

	trace_fib6_table_lookup(net, f6i, table, fl6);

	/* Search through exception table */
	rt = rt6_find_cached_rt(f6i, &fl6->daddr, &fl6->saddr);
	if (rt) {
		if (ip6_hold_safe(net, &rt, true))
			dst_use_noref(&rt->dst, jiffies);
	} else if (f6i == net->ipv6.fib6_null_entry) {
		rt = net->ipv6.ip6_null_entry;
		dst_hold(&rt->dst);
	} else {
		rt = ip6_create_rt_rcu(f6i);
	}

	rcu_read_unlock();

	return rt;
}