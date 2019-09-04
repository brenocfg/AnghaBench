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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_release_head_state (struct sk_buff*) ; 
 int /*<<< orphan*/  skbuff_head_cache ; 

void kfree_skb_partial(struct sk_buff *skb, bool head_stolen)
{
	if (head_stolen) {
		skb_release_head_state(skb);
		kmem_cache_free(skbuff_head_cache, skb);
	} else {
		__kfree_skb(skb);
	}
}