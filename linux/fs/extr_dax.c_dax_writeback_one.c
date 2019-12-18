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
struct xa_state {unsigned long xa_index; } ;
struct dax_device {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dax_entry_mkclean (struct address_space*,unsigned long,unsigned long) ; 
 unsigned long dax_entry_order (void*) ; 
 int /*<<< orphan*/  dax_flush (struct dax_device*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ dax_is_empty_entry (void*) ; 
 int /*<<< orphan*/  dax_is_locked (void*) ; 
 scalar_t__ dax_is_zero_entry (void*) ; 
 int /*<<< orphan*/  dax_lock_entry (struct xa_state*,void*) ; 
 scalar_t__ dax_to_pfn (void*) ; 
 int /*<<< orphan*/  dax_wake_entry (struct xa_state*,void*,int) ; 
 void* get_unlocked_entry (struct xa_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  put_unlocked_entry (struct xa_state*,void*) ; 
 int /*<<< orphan*/  trace_dax_writeback_one (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_is_value (void*) ; 
 int /*<<< orphan*/  xas_clear_mark (struct xa_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_get_mark (struct xa_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_lock_irq (struct xa_state*) ; 
 int /*<<< orphan*/  xas_reset (struct xa_state*) ; 
 int /*<<< orphan*/  xas_store (struct xa_state*,void*) ; 
 int /*<<< orphan*/  xas_unlock_irq (struct xa_state*) ; 

__attribute__((used)) static int dax_writeback_one(struct xa_state *xas, struct dax_device *dax_dev,
		struct address_space *mapping, void *entry)
{
	unsigned long pfn, index, count;
	long ret = 0;

	/*
	 * A page got tagged dirty in DAX mapping? Something is seriously
	 * wrong.
	 */
	if (WARN_ON(!xa_is_value(entry)))
		return -EIO;

	if (unlikely(dax_is_locked(entry))) {
		void *old_entry = entry;

		entry = get_unlocked_entry(xas, 0);

		/* Entry got punched out / reallocated? */
		if (!entry || WARN_ON_ONCE(!xa_is_value(entry)))
			goto put_unlocked;
		/*
		 * Entry got reallocated elsewhere? No need to writeback.
		 * We have to compare pfns as we must not bail out due to
		 * difference in lockbit or entry type.
		 */
		if (dax_to_pfn(old_entry) != dax_to_pfn(entry))
			goto put_unlocked;
		if (WARN_ON_ONCE(dax_is_empty_entry(entry) ||
					dax_is_zero_entry(entry))) {
			ret = -EIO;
			goto put_unlocked;
		}

		/* Another fsync thread may have already done this entry */
		if (!xas_get_mark(xas, PAGECACHE_TAG_TOWRITE))
			goto put_unlocked;
	}

	/* Lock the entry to serialize with page faults */
	dax_lock_entry(xas, entry);

	/*
	 * We can clear the tag now but we have to be careful so that concurrent
	 * dax_writeback_one() calls for the same index cannot finish before we
	 * actually flush the caches. This is achieved as the calls will look
	 * at the entry only under the i_pages lock and once they do that
	 * they will see the entry locked and wait for it to unlock.
	 */
	xas_clear_mark(xas, PAGECACHE_TAG_TOWRITE);
	xas_unlock_irq(xas);

	/*
	 * If dax_writeback_mapping_range() was given a wbc->range_start
	 * in the middle of a PMD, the 'index' we use needs to be
	 * aligned to the start of the PMD.
	 * This allows us to flush for PMD_SIZE and not have to worry about
	 * partial PMD writebacks.
	 */
	pfn = dax_to_pfn(entry);
	count = 1UL << dax_entry_order(entry);
	index = xas->xa_index & ~(count - 1);

	dax_entry_mkclean(mapping, index, pfn);
	dax_flush(dax_dev, page_address(pfn_to_page(pfn)), count * PAGE_SIZE);
	/*
	 * After we have flushed the cache, we can clear the dirty tag. There
	 * cannot be new dirty data in the pfn after the flush has completed as
	 * the pfn mappings are writeprotected and fault waits for mapping
	 * entry lock.
	 */
	xas_reset(xas);
	xas_lock_irq(xas);
	xas_store(xas, entry);
	xas_clear_mark(xas, PAGECACHE_TAG_DIRTY);
	dax_wake_entry(xas, entry, false);

	trace_dax_writeback_one(mapping->host, index, count);
	return ret;

 put_unlocked:
	put_unlocked_entry(xas, entry);
	return ret;
}