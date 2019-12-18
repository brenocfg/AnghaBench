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
struct fq_flow {scalar_t__ qlen; struct sk_buff* head; struct sk_buff* tail; int /*<<< orphan*/  t_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  rtnl_kfree_skbs (struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static void fq_flow_purge(struct fq_flow *flow)
{
	struct rb_node *p = rb_first(&flow->t_root);

	while (p) {
		struct sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);
		rb_erase(&skb->rbnode, &flow->t_root);
		rtnl_kfree_skbs(skb, skb);
	}
	rtnl_kfree_skbs(flow->head, flow->tail);
	flow->head = NULL;
	flow->qlen = 0;
}