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
 int /*<<< orphan*/  KASAN_FREE_PAGE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int /*<<< orphan*/  __kasan_slab_free (int /*<<< orphan*/ ,void*,unsigned long,int) ; 
 int compound_order (struct page*) ; 
 int /*<<< orphan*/  kasan_poison_shadow (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_report_invalid_free (void*,unsigned long) ; 
 void* page_address (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void*) ; 

void kasan_poison_kfree(void *ptr, unsigned long ip)
{
	struct page *page;

	page = virt_to_head_page(ptr);

	if (unlikely(!PageSlab(page))) {
		if (ptr != page_address(page)) {
			kasan_report_invalid_free(ptr, ip);
			return;
		}
		kasan_poison_shadow(ptr, PAGE_SIZE << compound_order(page),
				KASAN_FREE_PAGE);
	} else {
		__kasan_slab_free(page->slab_cache, ptr, ip, false);
	}
}