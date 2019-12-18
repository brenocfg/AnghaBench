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
struct page {int /*<<< orphan*/  slab_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int ZERO_OR_NULL_PTR (void const*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 unsigned int compound_order (struct page*) ; 
 int /*<<< orphan*/  kfree_hook (void*) ; 
 int /*<<< orphan*/  mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  slab_free (int /*<<< orphan*/ ,struct page*,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kfree (int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void const*) ; 

void kfree(const void *x)
{
	struct page *page;
	void *object = (void *)x;

	trace_kfree(_RET_IP_, x);

	if (unlikely(ZERO_OR_NULL_PTR(x)))
		return;

	page = virt_to_head_page(x);
	if (unlikely(!PageSlab(page))) {
		unsigned int order = compound_order(page);

		BUG_ON(!PageCompound(page));
		kfree_hook(object);
		mod_node_page_state(page_pgdat(page), NR_SLAB_UNRECLAIMABLE,
				    -(1 << order));
		__free_pages(page, order);
		return;
	}
	slab_free(page->slab_cache, page, object, NULL, 1, _RET_IP_);
}