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
struct flowidn {scalar_t__ saddr; scalar_t__ daddr; scalar_t__ flowidn_mark; scalar_t__ flowidn_oif; } ;
struct dst_entry {int dummy; } ;
struct TYPE_3__ {scalar_t__ daddr; scalar_t__ saddr; scalar_t__ flowidn_mark; scalar_t__ flowidn_oif; } ;
struct dn_route {struct dst_entry dst; TYPE_1__ fld; int /*<<< orphan*/  dn_next; } ;
struct TYPE_4__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int MSG_TRYHARD ; 
 unsigned int dn_hash (scalar_t__,scalar_t__) ; 
 scalar_t__ dn_is_output_route (struct dn_route*) ; 
 int dn_route_output_slow (struct dst_entry**,struct flowidn const*,int) ; 
 TYPE_2__* dn_rt_hash_table ; 
 int /*<<< orphan*/  dst_hold_and_use (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct dn_route* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static int __dn_route_output_key(struct dst_entry **pprt, const struct flowidn *flp, int flags)
{
	unsigned int hash = dn_hash(flp->saddr, flp->daddr);
	struct dn_route *rt = NULL;

	if (!(flags & MSG_TRYHARD)) {
		rcu_read_lock_bh();
		for (rt = rcu_dereference_bh(dn_rt_hash_table[hash].chain); rt;
			rt = rcu_dereference_bh(rt->dn_next)) {
			if ((flp->daddr == rt->fld.daddr) &&
			    (flp->saddr == rt->fld.saddr) &&
			    (flp->flowidn_mark == rt->fld.flowidn_mark) &&
			    dn_is_output_route(rt) &&
			    (rt->fld.flowidn_oif == flp->flowidn_oif)) {
				dst_hold_and_use(&rt->dst, jiffies);
				rcu_read_unlock_bh();
				*pprt = &rt->dst;
				return 0;
			}
		}
		rcu_read_unlock_bh();
	}

	return dn_route_output_slow(pprt, flp, flags);
}