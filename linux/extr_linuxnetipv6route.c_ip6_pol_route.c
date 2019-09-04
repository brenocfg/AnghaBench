#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rt6_info {int /*<<< orphan*/  dst; } ;
struct TYPE_6__ {struct rt6_info* ip6_null_entry; TYPE_2__* rt6_stats; struct fib6_info* fib6_null_entry; TYPE_1__* devconf_all; } ;
struct net {TYPE_3__ ipv6; } ;
struct flowi6 {int flowi6_flags; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct fib6_table {int dummy; } ;
struct fib6_info {int fib6_flags; scalar_t__ fib6_nsiblings; } ;
struct TYPE_5__ {int /*<<< orphan*/  fib_rt_uncache; } ;
struct TYPE_4__ {scalar_t__ forwarding; } ;

/* Variables and functions */
 int FLOWI_FLAG_KNOWN_NH ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RT6_LOOKUP_F_IGNORE_LINKSTATE ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_use_noref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fib6_info* fib6_multipath_select (struct net*,struct fib6_info*,struct flowi6*,int,struct sk_buff const*,int) ; 
 struct fib6_info* fib6_table_lookup (struct net*,struct fib6_table*,int,struct flowi6*,int) ; 
 scalar_t__ ip6_hold_safe (struct net*,struct rt6_info**,int) ; 
 struct rt6_info* ip6_rt_cache_alloc (struct fib6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rt6_info* rt6_find_cached_rt (struct fib6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_get_pcpu_route (struct fib6_info*) ; 
 struct rt6_info* rt6_make_pcpu_route (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_uncached_list_add (struct rt6_info*) ; 
 scalar_t__ unlikely (int) ; 

struct rt6_info *ip6_pol_route(struct net *net, struct fib6_table *table,
			       int oif, struct flowi6 *fl6,
			       const struct sk_buff *skb, int flags)
{
	struct fib6_info *f6i;
	struct rt6_info *rt;
	int strict = 0;

	strict |= flags & RT6_LOOKUP_F_IFACE;
	strict |= flags & RT6_LOOKUP_F_IGNORE_LINKSTATE;
	if (net->ipv6.devconf_all->forwarding == 0)
		strict |= RT6_LOOKUP_F_REACHABLE;

	rcu_read_lock();

	f6i = fib6_table_lookup(net, table, oif, fl6, strict);
	if (f6i->fib6_nsiblings)
		f6i = fib6_multipath_select(net, f6i, fl6, oif, skb, strict);

	if (f6i == net->ipv6.fib6_null_entry) {
		rt = net->ipv6.ip6_null_entry;
		rcu_read_unlock();
		dst_hold(&rt->dst);
		return rt;
	}

	/*Search through exception table */
	rt = rt6_find_cached_rt(f6i, &fl6->daddr, &fl6->saddr);
	if (rt) {
		if (ip6_hold_safe(net, &rt, true))
			dst_use_noref(&rt->dst, jiffies);

		rcu_read_unlock();
		return rt;
	} else if (unlikely((fl6->flowi6_flags & FLOWI_FLAG_KNOWN_NH) &&
			    !(f6i->fib6_flags & RTF_GATEWAY))) {
		/* Create a RTF_CACHE clone which will not be
		 * owned by the fib6 tree.  It is for the special case where
		 * the daddr in the skb during the neighbor look-up is different
		 * from the fl6->daddr used to look-up route here.
		 */
		struct rt6_info *uncached_rt;

		uncached_rt = ip6_rt_cache_alloc(f6i, &fl6->daddr, NULL);

		rcu_read_unlock();

		if (uncached_rt) {
			/* Uncached_rt's refcnt is taken during ip6_rt_cache_alloc()
			 * No need for another dst_hold()
			 */
			rt6_uncached_list_add(uncached_rt);
			atomic_inc(&net->ipv6.rt6_stats->fib_rt_uncache);
		} else {
			uncached_rt = net->ipv6.ip6_null_entry;
			dst_hold(&uncached_rt->dst);
		}

		return uncached_rt;
	} else {
		/* Get a percpu copy */

		struct rt6_info *pcpu_rt;

		local_bh_disable();
		pcpu_rt = rt6_get_pcpu_route(f6i);

		if (!pcpu_rt)
			pcpu_rt = rt6_make_pcpu_route(net, f6i);

		local_bh_enable();
		rcu_read_unlock();

		return pcpu_rt;
	}
}