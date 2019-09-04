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
struct fq_flow {struct sk_buff* tail; struct sk_buff* head; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 scalar_t__ skb_is_retransmit (struct sk_buff*) ; 

__attribute__((used)) static void flow_queue_add(struct fq_flow *flow, struct sk_buff *skb)
{
	struct sk_buff *prev, *head = flow->head;

	skb->next = NULL;
	if (!head) {
		flow->head = skb;
		flow->tail = skb;
		return;
	}
	if (likely(!skb_is_retransmit(skb))) {
		flow->tail->next = skb;
		flow->tail = skb;
		return;
	}

	/* This skb is a tcp retransmit,
	 * find the last retrans packet in the queue
	 */
	prev = NULL;
	while (skb_is_retransmit(head)) {
		prev = head;
		head = head->next;
		if (!head)
			break;
	}
	if (!prev) { /* no rtx packet in queue, become the new head */
		skb->next = flow->head;
		flow->head = skb;
	} else {
		if (prev == flow->tail)
			flow->tail = skb;
		else
			skb->next = prev->next;
		prev->next = skb;
	}
}