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
struct napi_alloc_cache {scalar_t__ skb_count; int /*<<< orphan*/  skb_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free_bulk (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_alloc_cache ; 
 int /*<<< orphan*/  skbuff_head_cache ; 
 struct napi_alloc_cache* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void __kfree_skb_flush(void)
{
	struct napi_alloc_cache *nc = this_cpu_ptr(&napi_alloc_cache);

	/* flush skb_cache if containing objects */
	if (nc->skb_count) {
		kmem_cache_free_bulk(skbuff_head_cache, nc->skb_count,
				     nc->skb_cache);
		nc->skb_count = 0;
	}
}