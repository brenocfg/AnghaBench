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
struct pagevec {struct page** pages; } ;
struct page {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FS_DAX_LIMITED ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGEVEC_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct page* dax_busy_page (void*) ; 
 int /*<<< orphan*/  dax_mapping (struct address_space*) ; 
 unsigned long dax_radix_order (void*) ; 
 void* get_unlocked_mapping_entry (struct address_space*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 scalar_t__ pagevec_lookup_entries (struct pagevec*,struct address_space*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_remove_exceptionals (struct pagevec*) ; 
 int /*<<< orphan*/  put_unlocked_mapping_entry (struct address_space*,int,void*) ; 
 int /*<<< orphan*/  radix_tree_exceptional_entry (struct page*) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

struct page *dax_layout_busy_page(struct address_space *mapping)
{
	pgoff_t	indices[PAGEVEC_SIZE];
	struct page *page = NULL;
	struct pagevec pvec;
	pgoff_t	index, end;
	unsigned i;

	/*
	 * In the 'limited' case get_user_pages() for dax is disabled.
	 */
	if (IS_ENABLED(CONFIG_FS_DAX_LIMITED))
		return NULL;

	if (!dax_mapping(mapping) || !mapping_mapped(mapping))
		return NULL;

	pagevec_init(&pvec);
	index = 0;
	end = -1;

	/*
	 * If we race get_user_pages_fast() here either we'll see the
	 * elevated page count in the pagevec_lookup and wait, or
	 * get_user_pages_fast() will see that the page it took a reference
	 * against is no longer mapped in the page tables and bail to the
	 * get_user_pages() slow path.  The slow path is protected by
	 * pte_lock() and pmd_lock(). New references are not taken without
	 * holding those locks, and unmap_mapping_range() will not zero the
	 * pte or pmd without holding the respective lock, so we are
	 * guaranteed to either see new references or prevent new
	 * references from being established.
	 */
	unmap_mapping_range(mapping, 0, 0, 1);

	while (index < end && pagevec_lookup_entries(&pvec, mapping, index,
				min(end - index, (pgoff_t)PAGEVEC_SIZE),
				indices)) {
		pgoff_t nr_pages = 1;

		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *pvec_ent = pvec.pages[i];
			void *entry;

			index = indices[i];
			if (index >= end)
				break;

			if (WARN_ON_ONCE(
			     !radix_tree_exceptional_entry(pvec_ent)))
				continue;

			xa_lock_irq(&mapping->i_pages);
			entry = get_unlocked_mapping_entry(mapping, index, NULL);
			if (entry) {
				page = dax_busy_page(entry);
				/*
				 * Account for multi-order entries at
				 * the end of the pagevec.
				 */
				if (i + 1 >= pagevec_count(&pvec))
					nr_pages = 1UL << dax_radix_order(entry);
			}
			put_unlocked_mapping_entry(mapping, index, entry);
			xa_unlock_irq(&mapping->i_pages);
			if (page)
				break;
		}

		/*
		 * We don't expect normal struct page entries to exist in our
		 * tree, but we keep these pagevec calls so that this code is
		 * consistent with the common pattern for handling pagevecs
		 * throughout the kernel.
		 */
		pagevec_remove_exceptionals(&pvec);
		pagevec_release(&pvec);
		index += nr_pages;

		if (page)
			break;
	}
	return page;
}