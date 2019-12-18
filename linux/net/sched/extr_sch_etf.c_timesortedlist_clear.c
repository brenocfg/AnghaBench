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
struct sk_buff {int /*<<< orphan*/  rbnode; } ;
struct rb_node {int dummy; } ;
struct etf_sched_data {int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_first_cached (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  rtnl_kfree_skbs (struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static void timesortedlist_clear(struct Qdisc *sch)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct rb_node *p = rb_first_cached(&q->head);

	while (p) {
		struct sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);

		rb_erase_cached(&skb->rbnode, &q->head);
		rtnl_kfree_skbs(skb, skb);
		sch->q.qlen--;
	}
}