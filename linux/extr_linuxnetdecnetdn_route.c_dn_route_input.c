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
struct sk_buff {scalar_t__ mark; } ;
struct dst_entry {int dummy; } ;
struct dn_skb_cb {scalar_t__ src; scalar_t__ dst; scalar_t__ iif; } ;
struct TYPE_3__ {scalar_t__ saddr; scalar_t__ daddr; scalar_t__ flowidn_oif; scalar_t__ flowidn_mark; scalar_t__ flowidn_iif; } ;
struct dn_route {int /*<<< orphan*/  dst; TYPE_1__ fld; int /*<<< orphan*/  dn_next; } ;
struct TYPE_4__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 unsigned int dn_hash (scalar_t__,scalar_t__) ; 
 int dn_route_input_slow (struct sk_buff*) ; 
 TYPE_2__* dn_rt_hash_table ; 
 int /*<<< orphan*/  dst_hold_and_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct dn_route* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 

__attribute__((used)) static int dn_route_input(struct sk_buff *skb)
{
	struct dn_route *rt;
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	unsigned int hash = dn_hash(cb->src, cb->dst);

	if (skb_dst(skb))
		return 0;

	rcu_read_lock();
	for(rt = rcu_dereference(dn_rt_hash_table[hash].chain); rt != NULL;
	    rt = rcu_dereference(rt->dn_next)) {
		if ((rt->fld.saddr == cb->src) &&
		    (rt->fld.daddr == cb->dst) &&
		    (rt->fld.flowidn_oif == 0) &&
		    (rt->fld.flowidn_mark == skb->mark) &&
		    (rt->fld.flowidn_iif == cb->iif)) {
			dst_hold_and_use(&rt->dst, jiffies);
			rcu_read_unlock();
			skb_dst_set(skb, (struct dst_entry *)rt);
			return 0;
		}
	}
	rcu_read_unlock();

	return dn_route_input_slow(skb);
}