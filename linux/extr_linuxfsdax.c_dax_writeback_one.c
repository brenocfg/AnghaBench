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
struct radix_tree_root {int dummy; } ;
struct dax_device {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; struct radix_tree_root i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dax_flush (struct dax_device*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ dax_is_empty_entry (void*) ; 
 scalar_t__ dax_is_zero_entry (void*) ; 
 int /*<<< orphan*/  dax_mapping_entry_mkclean (struct address_space*,int /*<<< orphan*/ ,unsigned long) ; 
 size_t dax_radix_order (void*) ; 
 scalar_t__ dax_radix_pfn (void*) ; 
 void* get_unlocked_mapping_entry (struct address_space*,int /*<<< orphan*/ ,void***) ; 
 void* lock_slot (struct address_space*,void**) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  put_locked_mapping_entry (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unlocked_mapping_entry (struct address_space*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  radix_tree_exceptional_entry (void*) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (struct radix_tree_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_get (struct radix_tree_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dax_writeback_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xa_lock_irq (struct radix_tree_root*) ; 
 int /*<<< orphan*/  xa_unlock_irq (struct radix_tree_root*) ; 

__attribute__((used)) static int dax_writeback_one(struct dax_device *dax_dev,
		struct address_space *mapping, pgoff_t index, void *entry)
{
	struct radix_tree_root *pages = &mapping->i_pages;
	void *entry2, **slot;
	unsigned long pfn;
	long ret = 0;
	size_t size;

	/*
	 * A page got tagged dirty in DAX mapping? Something is seriously
	 * wrong.
	 */
	if (WARN_ON(!radix_tree_exceptional_entry(entry)))
		return -EIO;

	xa_lock_irq(pages);
	entry2 = get_unlocked_mapping_entry(mapping, index, &slot);
	/* Entry got punched out / reallocated? */
	if (!entry2 || WARN_ON_ONCE(!radix_tree_exceptional_entry(entry2)))
		goto put_unlocked;
	/*
	 * Entry got reallocated elsewhere? No need to writeback. We have to
	 * compare pfns as we must not bail out due to difference in lockbit
	 * or entry type.
	 */
	if (dax_radix_pfn(entry2) != dax_radix_pfn(entry))
		goto put_unlocked;
	if (WARN_ON_ONCE(dax_is_empty_entry(entry) ||
				dax_is_zero_entry(entry))) {
		ret = -EIO;
		goto put_unlocked;
	}

	/* Another fsync thread may have already written back this entry */
	if (!radix_tree_tag_get(pages, index, PAGECACHE_TAG_TOWRITE))
		goto put_unlocked;
	/* Lock the entry to serialize with page faults */
	entry = lock_slot(mapping, slot);
	/*
	 * We can clear the tag now but we have to be careful so that concurrent
	 * dax_writeback_one() calls for the same index cannot finish before we
	 * actually flush the caches. This is achieved as the calls will look
	 * at the entry only under the i_pages lock and once they do that
	 * they will see the entry locked and wait for it to unlock.
	 */
	radix_tree_tag_clear(pages, index, PAGECACHE_TAG_TOWRITE);
	xa_unlock_irq(pages);

	/*
	 * Even if dax_writeback_mapping_range() was given a wbc->range_start
	 * in the middle of a PMD, the 'index' we are given will be aligned to
	 * the start index of the PMD, as will the pfn we pull from 'entry'.
	 * This allows us to flush for PMD_SIZE and not have to worry about
	 * partial PMD writebacks.
	 */
	pfn = dax_radix_pfn(entry);
	size = PAGE_SIZE << dax_radix_order(entry);

	dax_mapping_entry_mkclean(mapping, index, pfn);
	dax_flush(dax_dev, page_address(pfn_to_page(pfn)), size);
	/*
	 * After we have flushed the cache, we can clear the dirty tag. There
	 * cannot be new dirty data in the pfn after the flush has completed as
	 * the pfn mappings are writeprotected and fault waits for mapping
	 * entry lock.
	 */
	xa_lock_irq(pages);
	radix_tree_tag_clear(pages, index, PAGECACHE_TAG_DIRTY);
	xa_unlock_irq(pages);
	trace_dax_writeback_one(mapping->host, index, size >> PAGE_SHIFT);
	put_locked_mapping_entry(mapping, index);
	return ret;

 put_unlocked:
	put_unlocked_mapping_entry(mapping, index, entry2);
	xa_unlock_irq(pages);
	return ret;
}