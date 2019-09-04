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

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static inline void vnet_free_skbs(struct sk_buff *skb)
{
	struct sk_buff *next;

	while (skb) {
		next = skb->next;
		skb->next = NULL;
		dev_kfree_skb(skb);
		skb = next;
	}
}