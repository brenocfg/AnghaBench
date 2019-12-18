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
struct fq_flow {struct sk_buff* head; int /*<<< orphan*/  t_root; } ;
struct TYPE_2__ {scalar_t__ time_to_send; } ;

/* Variables and functions */
 TYPE_1__* fq_skb_cb (struct sk_buff*) ; 
 struct sk_buff* skb_rb_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *fq_peek(struct fq_flow *flow)
{
	struct sk_buff *skb = skb_rb_first(&flow->t_root);
	struct sk_buff *head = flow->head;

	if (!skb)
		return head;

	if (!head)
		return skb;

	if (fq_skb_cb(skb)->time_to_send < fq_skb_cb(head)->time_to_send)
		return skb;
	return head;
}