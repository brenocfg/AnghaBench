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
struct zone {int /*<<< orphan*/  zone_pgdat; } ;
struct page {int /*<<< orphan*/  mapping; int /*<<< orphan*/  index; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int EAGAIN ; 
 int HPAGE_PMD_NR ; 
 int MIGRATEPAGE_SUCCESS ; 
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
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __SetPageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  __dec_node_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dec_zone_state (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_node_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_zone_state (struct zone*,int /*<<< orphan*/ ) ; 
 int expected_page_refs (struct address_space*,struct page*) ; 
 scalar_t__ hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,scalar_t__) ; 
 int /*<<< orphan*/  page_ref_freeze (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_unfreeze (struct page*,scalar_t__) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas ; 
 struct page* xas_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  xas_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_unlock_irq (int /*<<< orphan*/ *) ; 

int migrate_page_move_mapping(struct address_space *mapping,
		struct page *newpage, struct page *page, int extra_count)
{
	XA_STATE(xas, &mapping->i_pages, page_index(page));
	struct zone *oldzone, *newzone;
	int dirty;
	int expected_count = expected_page_refs(mapping, page) + extra_count;

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

	xas_lock_irq(&xas);
	if (page_count(page) != expected_count || xas_load(&xas) != page) {
		xas_unlock_irq(&xas);
		return -EAGAIN;
	}

	if (!page_ref_freeze(page, expected_count)) {
		xas_unlock_irq(&xas);
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

	xas_store(&xas, newpage);
	if (PageTransHuge(page)) {
		int i;

		for (i = 1; i < HPAGE_PMD_NR; i++) {
			xas_next(&xas);
			xas_store(&xas, newpage);
		}
	}

	/*
	 * Drop cache reference from old page by unfreezing
	 * to one less reference.
	 * We know this isn't the last reference.
	 */
	page_ref_unfreeze(page, expected_count - hpage_nr_pages(page));

	xas_unlock(&xas);
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