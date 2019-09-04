#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct zone {int /*<<< orphan*/  zone_pgdat; } ;
struct page {int /*<<< orphan*/  mapping; int /*<<< orphan*/  index; } ;
struct buffer_head {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  xa_lock; } ;
struct address_space {TYPE_1__ i_pages; } ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int EAGAIN ; 
 int HPAGE_PMD_NR ; 
 int MIGRATEPAGE_SUCCESS ; 
 int MIGRATE_ASYNC ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  NR_SHMEM ; 
 int /*<<< orphan*/  NR_ZONE_WRITE_PENDING ; 
 int PageDirty (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (scalar_t__,struct page*) ; 
 int /*<<< orphan*/  __SetPageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  __dec_node_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dec_zone_state (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_node_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_zone_state (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_migrate_lock_buffers (struct buffer_head*,int) ; 
 int hpage_nr_pages (struct page*) ; 
 scalar_t__ is_device_private_page (struct page*) ; 
 scalar_t__ is_device_public_page (struct page*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int page_count (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int page_index (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_freeze (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_unfreeze (struct page*,int) ; 
 struct zone* page_zone (struct page*) ; 
 struct page* radix_tree_deref_slot_protected (void**,int /*<<< orphan*/ *) ; 
 void** radix_tree_lookup_slot (TYPE_1__*,int) ; 
 int /*<<< orphan*/  radix_tree_replace_slot (TYPE_1__*,void**,struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  xa_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  xa_unlock_irq (TYPE_1__*) ; 

int migrate_page_move_mapping(struct address_space *mapping,
		struct page *newpage, struct page *page,
		struct buffer_head *head, enum migrate_mode mode,
		int extra_count)
{
	struct zone *oldzone, *newzone;
	int dirty;
	int expected_count = 1 + extra_count;
	void **pslot;

	/*
	 * Device public or private pages have an extra refcount as they are
	 * ZONE_DEVICE pages.
	 */
	expected_count += is_device_private_page(page);
	expected_count += is_device_public_page(page);

	if (!mapping) {
		/* Anonymous page without mapping */
		if (page_count(page) != expected_count)
			return -EAGAIN;

		/* No turning back from here */
		newpage->index = page->index;
		newpage->mapping = page->mapping;
		if (PageSwapBacked(page))
			__SetPageSwapBacked(newpage);

		return MIGRATEPAGE_SUCCESS;
	}

	oldzone = page_zone(page);
	newzone = page_zone(newpage);

	xa_lock_irq(&mapping->i_pages);

	pslot = radix_tree_lookup_slot(&mapping->i_pages,
 					page_index(page));

	expected_count += hpage_nr_pages(page) + page_has_private(page);
	if (page_count(page) != expected_count ||
		radix_tree_deref_slot_protected(pslot,
					&mapping->i_pages.xa_lock) != page) {
		xa_unlock_irq(&mapping->i_pages);
		return -EAGAIN;
	}

	if (!page_ref_freeze(page, expected_count)) {
		xa_unlock_irq(&mapping->i_pages);
		return -EAGAIN;
	}

	/*
	 * In the async migration case of moving a page with buffers, lock the
	 * buffers using trylock before the mapping is moved. If the mapping
	 * was moved, we later failed to lock the buffers and could not move
	 * the mapping back due to an elevated page count, we would have to
	 * block waiting on other references to be dropped.
	 */
	if (mode == MIGRATE_ASYNC && head &&
			!buffer_migrate_lock_buffers(head, mode)) {
		page_ref_unfreeze(page, expected_count);
		xa_unlock_irq(&mapping->i_pages);
		return -EAGAIN;
	}

	/*
	 * Now we know that no one else is looking at the page:
	 * no turning back from here.
	 */
	newpage->index = page->index;
	newpage->mapping = page->mapping;
	page_ref_add(newpage, hpage_nr_pages(page)); /* add cache reference */
	if (PageSwapBacked(page)) {
		__SetPageSwapBacked(newpage);
		if (PageSwapCache(page)) {
			SetPageSwapCache(newpage);
			set_page_private(newpage, page_private(page));
		}
	} else {
		VM_BUG_ON_PAGE(PageSwapCache(page), page);
	}

	/* Move dirty while page refs frozen and newpage not yet exposed */
	dirty = PageDirty(page);
	if (dirty) {
		ClearPageDirty(page);
		SetPageDirty(newpage);
	}

	radix_tree_replace_slot(&mapping->i_pages, pslot, newpage);
	if (PageTransHuge(page)) {
		int i;
		int index = page_index(page);

		for (i = 1; i < HPAGE_PMD_NR; i++) {
			pslot = radix_tree_lookup_slot(&mapping->i_pages,
						       index + i);
			radix_tree_replace_slot(&mapping->i_pages, pslot,
						newpage + i);
		}
	}

	/*
	 * Drop cache reference from old page by unfreezing
	 * to one less reference.
	 * We know this isn't the last reference.
	 */
	page_ref_unfreeze(page, expected_count - hpage_nr_pages(page));

	xa_unlock(&mapping->i_pages);
	/* Leave irq disabled to prevent preemption while updating stats */

	/*
	 * If moved to a different zone then also account
	 * the page for that zone. Other VM counters will be
	 * taken care of when we establish references to the
	 * new page and drop references to the old page.
	 *
	 * Note that anonymous pages are accounted for
	 * via NR_FILE_PAGES and NR_ANON_MAPPED if they
	 * are mapped to swap space.
	 */
	if (newzone != oldzone) {
		__dec_node_state(oldzone->zone_pgdat, NR_FILE_PAGES);
		__inc_node_state(newzone->zone_pgdat, NR_FILE_PAGES);
		if (PageSwapBacked(page) && !PageSwapCache(page)) {
			__dec_node_state(oldzone->zone_pgdat, NR_SHMEM);
			__inc_node_state(newzone->zone_pgdat, NR_SHMEM);
		}
		if (dirty && mapping_cap_account_dirty(mapping)) {
			__dec_node_state(oldzone->zone_pgdat, NR_FILE_DIRTY);
			__dec_zone_state(oldzone, NR_ZONE_WRITE_PENDING);
			__inc_node_state(newzone->zone_pgdat, NR_FILE_DIRTY);
			__inc_zone_state(newzone, NR_ZONE_WRITE_PENDING);
		}
	}
	local_irq_enable();

	return MIGRATEPAGE_SUCCESS;
}