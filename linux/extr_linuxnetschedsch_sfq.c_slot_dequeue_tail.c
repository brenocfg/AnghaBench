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
struct sk_buff {struct sk_buff* prev; struct sk_buff* next; } ;
struct sfq_slot {struct sk_buff* skblist_prev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sk_buff *slot_dequeue_tail(struct sfq_slot *slot)
{
	struct sk_buff *skb = slot->skblist_prev;

	slot->skblist_prev = skb->prev;
	skb->prev->next = (struct sk_buff *)slot;
	skb->next = skb->prev = NULL;
	return skb;
}