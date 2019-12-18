#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rt6_info {int dummy; } ;
struct TYPE_8__ {scalar_t__ fib6_null_entry; struct rt6_info* ip6_null_entry; TYPE_3__* rt6_stats; TYPE_1__* devconf_all; } ;
struct net {TYPE_4__ ipv6; } ;
struct flowi6 {int flowi6_flags; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct fib6_table {int dummy; } ;
struct fib6_result {scalar_t__ f6i; TYPE_2__* nh; } ;
struct TYPE_7__ {int /*<<< orphan*/  fib_rt_uncache; } ;
struct TYPE_6__ {int /*<<< orphan*/  fib_nh_gw_family; } ;
struct TYPE_5__ {scalar_t__ forwarding; } ;

/* Variables and functions */
 int FLOWI_FLAG_KNOWN_NH ; 
 int RT6_LOOKUP_F_DST_NOREF ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RT6_LOOKUP_F_IGNORE_LINKSTATE ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fib6_select_path (struct net*,struct fib6_result*,struct flowi6*,int,int,struct sk_buff const*,int) ; 
 int /*<<< orphan*/  fib6_table_lookup (struct net*,struct fib6_table*,int,struct flowi6*,struct fib6_result*,int) ; 
 int /*<<< orphan*/  ip6_hold_safe (struct net*,struct rt6_info**) ; 
 struct rt6_info* ip6_rt_cache_alloc (struct fib6_result*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rt6_info* rt6_find_cached_rt (struct fib6_result*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_get_pcpu_route (struct fib6_result*) ; 
 struct rt6_info* rt6_make_pcpu_route (struct net*,struct fib6_result*) ; 
 int /*<<< orphan*/  rt6_uncached_list_add (struct rt6_info*) ; 
 scalar_t__ unlikely (int) ; 

struct rt6_info *ip6_pol_route(struct net *net, struct fib6_table *table,
			       int oif, struct flowi6 *fl6,
			       const struct sk_buff *skb, int flags)
{
	struct fib6_result res = {};
	struct rt6_info *rt = NULL;
	int strict = 0;

	WARN_ON_ONCE((flags & RT6_LOOKUP_F_DST_NOREF) &&
		     !rcu_read_lock_held());

	strict |= flags & RT6_LOOKUP_F_IFACE;
	strict |= flags & RT6_LOOKUP_F_IGNORE_LINKSTATE;
	if (net->ipv6.devconf_all->forwarding == 0)
		strict |= RT6_LOOKUP_F_REACHABLE;

	rcu_read_lock();

	fib6_table_lookup(net, table, oif, fl6, &res, strict);
	if (res.f6i == net->ipv6.fib6_null_entry)
		goto out;

	fib6_select_path(net, &res, fl6, oif, false, skb, strict);

	/*Search through exception table */
	rt = rt6_find_cached_rt(&res, &fl6->daddr, &fl6->saddr);
	if (rt) {
		goto out;
	} else if (unlikely((fl6->flowi6_flags & FLOWI_FLAG_KNOWN_NH) &&
			    !res.nh->fib_nh_gw_family)) {
		/* Create a RTF_CACHE clone which will not be
		 * owned by the fib6 tree.  It is for the special case where
		 * the daddr in the skb during the neighbor look-up is different
		 * from the fl6->daddr used to look-up route here.
		 */
		rt = ip6_rt_cache_alloc(&res, &fl6->daddr, NULL);

		if (rt) {
			/* 1 refcnt is taken during ip6_rt_cache_alloc().
			 * As rt6_uncached_list_add() does not consume refcnt,
			 * this refcnt is always returned to the caller even
			 * if caller sets RT6_LOOKUP_F_DST_NOREF flag.
			 */
			rt6_uncached_list_add(rt);
			atomic_inc(&net->ipv6.rt6_stats->fib_rt_uncache);
			rcu_read_unlock();

			return rt;
		}
	} else {
		/* Get a percpu copy */
		local_bh_disable();
		rt = rt6_get_pcpu_route(&res);

		if (!rt)
			rt = rt6_make_pcpu_route(net, &res);

		local_bh_enable();
	}
out:
	if (!rt)
		rt = net->ipv6.ip6_null_entry;
	if (!(flags & RT6_LOOKUP_F_DST_NOREF))
		ip6_hold_safe(net, &rt);
	rcu_read_unlock();

	return rt;
}