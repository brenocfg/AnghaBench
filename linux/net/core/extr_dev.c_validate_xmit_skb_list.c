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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 
 struct sk_buff* validate_xmit_skb (struct sk_buff*,struct net_device*,int*) ; 

struct sk_buff *validate_xmit_skb_list(struct sk_buff *skb, struct net_device *dev, bool *again)
{
	struct sk_buff *next, *head = NULL, *tail;

	for (; skb != NULL; skb = next) {
		next = skb->next;
		skb_mark_not_on_list(skb);

		/* in case skb wont be segmented, point to itself */
		skb->prev = skb;

		skb = validate_xmit_skb(skb, dev, again);
		if (!skb)
			continue;

		if (!head)
			head = skb;
		else
			tail->next = skb;
		/* If skb was segmented, skb->prev points to
		 * the last segment. If not, it still contains skb.
		 */
		tail = skb->prev;
	}
	return head;
}