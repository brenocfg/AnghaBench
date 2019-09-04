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
struct sk_buff {scalar_t__ data_len; scalar_t__ end; scalar_t__ tail; int /*<<< orphan*/  truesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKB_TRUESIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pskb_pull_tail (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_end_offset (struct sk_buff*) ; 

void skb_condense(struct sk_buff *skb)
{
	if (skb->data_len) {
		if (skb->data_len > skb->end - skb->tail ||
		    skb_cloned(skb))
			return;

		/* Nice, we can free page frag(s) right now */
		__pskb_pull_tail(skb, skb->data_len);
	}
	/* At this point, skb->truesize might be over estimated,
	 * because skb had a fragment, and fragments do not tell
	 * their truesize.
	 * When we pulled its content into skb->head, fragment
	 * was freed, but __pskb_pull_tail() could not possibly
	 * adjust skb->truesize, not knowing the frag truesize.
	 */
	skb->truesize = SKB_TRUESIZE(skb_end_offset(skb));
}