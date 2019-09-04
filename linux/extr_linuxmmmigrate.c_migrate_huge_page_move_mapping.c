#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  mapping; int /*<<< orphan*/  index; } ;
struct TYPE_5__ {int /*<<< orphan*/  xa_lock; } ;
struct address_space {TYPE_1__ i_pages; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MIGRATEPAGE_SUCCESS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int page_count (struct page*) ; 
 int page_has_private (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  page_ref_freeze (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_unfreeze (struct page*,int) ; 
 struct page* radix_tree_deref_slot_protected (void**,int /*<<< orphan*/ *) ; 
 void** radix_tree_lookup_slot (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_replace_slot (TYPE_1__*,void**,struct page*) ; 
 int /*<<< orphan*/  xa_lock_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  xa_unlock_irq (TYPE_1__*) ; 

int migrate_huge_page_move_mapping(struct address_space *mapping,
				   struct page *newpage, struct page *page)
{
	int expected_count;
	void **pslot;

	xa_lock_irq(&mapping->i_pages);

	pslot = radix_tree_lookup_slot(&mapping->i_pages, page_index(page));

	expected_count = 2 + page_has_private(page);
	if (page_count(page) != expected_count ||
		radix_tree_deref_slot_protected(pslot, &mapping->i_pages.xa_lock) != page) {
		xa_unlock_irq(&mapping->i_pages);
		return -EAGAIN;
	}

	if (!page_ref_freeze(page, expected_count)) {
		xa_unlock_irq(&mapping->i_pages);
		return -EAGAIN;
	}

	newpage->index = page->index;
	newpage->mapping = page->mapping;

	get_page(newpage);

	radix_tree_replace_slot(&mapping->i_pages, pslot, newpage);

	page_ref_unfreeze(page, expected_count - 1);

	xa_unlock_irq(&mapping->i_pages);

	return MIGRATEPAGE_SUCCESS;
}