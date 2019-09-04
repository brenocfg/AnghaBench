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
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int ZERO_OR_NULL_PTR (void const*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compound_order (struct page*) ; 
 int /*<<< orphan*/  kfree_hook (void*) ; 
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
		BUG_ON(!PageCompound(page));
		kfree_hook(object);
		__free_pages(page, compound_order(page));
		return;
	}
	slab_free(page->slab_cache, page, object, NULL, 1, _RET_IP_);
}