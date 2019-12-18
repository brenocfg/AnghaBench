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
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_ext_put (struct sk_buff*) ; 
 int /*<<< orphan*/  skbuff_head_cache ; 

__attribute__((used)) static void napi_skb_free_stolen_head(struct sk_buff *skb)
{
	skb_dst_drop(skb);
	skb_ext_put(skb);
	kmem_cache_free(skbuff_head_cache, skb);
}