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
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void const* ZERO_SIZE_PTR ; 
 size_t page_size (struct page*) ; 
 size_t slab_ksize (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void const*) ; 

size_t __ksize(const void *object)
{
	struct page *page;

	if (unlikely(object == ZERO_SIZE_PTR))
		return 0;

	page = virt_to_head_page(object);

	if (unlikely(!PageSlab(page))) {
		WARN_ON(!PageCompound(page));
		return page_size(page);
	}

	return slab_ksize(page->slab_cache);
}