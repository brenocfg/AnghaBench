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
struct sk_buff {int end; int tail; int truesize; int /*<<< orphan*/  head; int /*<<< orphan*/ * sk; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ is_vmalloc_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *netlink_trim(struct sk_buff *skb, gfp_t allocation)
{
	int delta;

	WARN_ON(skb->sk != NULL);
	delta = skb->end - skb->tail;
	if (is_vmalloc_addr(skb->head) || delta * 2 < skb->truesize)
		return skb;

	if (skb_shared(skb)) {
		struct sk_buff *nskb = skb_clone(skb, allocation);
		if (!nskb)
			return skb;
		consume_skb(skb);
		skb = nskb;
	}

	pskb_expand_head(skb, 0, -delta,
			 (allocation & ~__GFP_DIRECT_RECLAIM) |
			 __GFP_NOWARN | __GFP_NORETRY);
	return skb;
}