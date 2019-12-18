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
struct sk_buff {struct sk_buff* next; } ;
struct Qdisc {struct sk_buff* (* dequeue ) (struct Qdisc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_enqueue_skb_bad_txq (struct Qdisc*,struct sk_buff*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void try_bulk_dequeue_skb_slow(struct Qdisc *q,
				      struct sk_buff *skb,
				      int *packets)
{
	int mapping = skb_get_queue_mapping(skb);
	struct sk_buff *nskb;
	int cnt = 0;

	do {
		nskb = q->dequeue(q);
		if (!nskb)
			break;
		if (unlikely(skb_get_queue_mapping(nskb) != mapping)) {
			qdisc_enqueue_skb_bad_txq(q, nskb);
			break;
		}
		skb->next = nskb;
		skb = nskb;
	} while (++cnt < 8);
	(*packets) += cnt;
	skb_mark_not_on_list(skb);
}