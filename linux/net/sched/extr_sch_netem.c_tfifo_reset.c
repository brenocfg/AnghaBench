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
struct sk_buff {int /*<<< orphan*/  rbnode; } ;
struct rb_node {int dummy; } ;
struct netem_sched_data {struct sk_buff* t_tail; struct sk_buff* t_head; int /*<<< orphan*/  t_root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  rtnl_kfree_skbs (struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static void tfifo_reset(struct Qdisc *sch)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	struct rb_node *p = rb_first(&q->t_root);

	while (p) {
		struct sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);
		rb_erase(&skb->rbnode, &q->t_root);
		rtnl_kfree_skbs(skb, skb);
	}

	rtnl_kfree_skbs(q->t_head, q->t_tail);
	q->t_head = NULL;
	q->t_tail = NULL;
}