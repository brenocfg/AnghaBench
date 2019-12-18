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
typedef  scalar_t__ u64 ;
struct sk_buff {int dummy; } ;
struct netem_sched_data {struct sk_buff* t_head; int /*<<< orphan*/  t_root; } ;
struct TYPE_2__ {scalar_t__ time_to_send; } ;

/* Variables and functions */
 TYPE_1__* netem_skb_cb (struct sk_buff*) ; 
 struct sk_buff* skb_rb_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *netem_peek(struct netem_sched_data *q)
{
	struct sk_buff *skb = skb_rb_first(&q->t_root);
	u64 t1, t2;

	if (!skb)
		return q->t_head;
	if (!q->t_head)
		return skb;

	t1 = netem_skb_cb(skb)->time_to_send;
	t2 = netem_skb_cb(q->t_head)->time_to_send;
	if (t1 < t2)
		return skb;
	return q->t_head;
}