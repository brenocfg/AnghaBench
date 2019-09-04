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
struct qdisc_skb_head {int /*<<< orphan*/  qlen; struct sk_buff* head; struct sk_buff* tail; } ;

/* Variables and functions */

__attribute__((used)) static void netem_enqueue_skb_head(struct qdisc_skb_head *qh, struct sk_buff *skb)
{
	skb->next = qh->head;

	if (!qh->head)
		qh->tail = skb;
	qh->head = skb;
	qh->qlen++;
}