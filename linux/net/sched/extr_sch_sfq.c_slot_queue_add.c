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
struct sk_buff {struct sk_buff* next; struct sk_buff* prev; } ;
struct sfq_slot {struct sk_buff* skblist_prev; } ;

/* Variables and functions */

__attribute__((used)) static inline void slot_queue_add(struct sfq_slot *slot, struct sk_buff *skb)
{
	skb->prev = slot->skblist_prev;
	skb->next = (struct sk_buff *)slot;
	slot->skblist_prev->next = skb;
	slot->skblist_prev = skb;
}