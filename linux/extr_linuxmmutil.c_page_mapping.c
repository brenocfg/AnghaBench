#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {void* mapping; } ;
typedef  void address_space ;

/* Variables and functions */
 unsigned long PAGE_MAPPING_ANON ; 
 unsigned long PAGE_MAPPING_FLAGS ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 void* swap_address_space (TYPE_1__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct address_space *page_mapping(struct page *page)
{
	struct address_space *mapping;

	page = compound_head(page);

	/* This happens if someone calls flush_dcache_page on slab page */
	if (unlikely(PageSlab(page)))
		return NULL;

	if (unlikely(PageSwapCache(page))) {
		swp_entry_t entry;

		entry.val = page_private(page);
		return swap_address_space(entry);
	}

	mapping = page->mapping;
	if ((unsigned long)mapping & PAGE_MAPPING_ANON)
		return NULL;

	return (void *)((unsigned long)mapping & ~PAGE_MAPPING_FLAGS);
}