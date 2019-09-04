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
struct address_space {int /*<<< orphan*/  i_pages; int /*<<< orphan*/  nrexceptional; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int EEXIST ; 
 int EIO ; 
 void* ERR_PTR (int) ; 
 int PG_PMD_COLOUR ; 
 int /*<<< orphan*/  PG_PMD_NR ; 
 unsigned long RADIX_DAX_EMPTY ; 
 unsigned long RADIX_DAX_PMD ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int __GFP_HIGHMEM ; 
 int __radix_tree_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 void* __radix_tree_lookup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void***) ; 
 int /*<<< orphan*/  dax_disassociate_entry (void*,struct address_space*,int) ; 
 scalar_t__ dax_is_empty_entry (void*) ; 
 scalar_t__ dax_is_pmd_entry (void*) ; 
 scalar_t__ dax_is_pte_entry (void*) ; 
 scalar_t__ dax_is_zero_entry (void*) ; 
 void* dax_radix_locked_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dax_radix_order (void*) ; 
 int /*<<< orphan*/  dax_wake_mapping_entry_waiter (struct address_space*,int,void*,int) ; 
 void* get_unlocked_mapping_entry (struct address_space*,int,void***) ; 
 void* lock_slot (struct address_space*,void**) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  put_locked_mapping_entry (struct address_space*,int) ; 
 int /*<<< orphan*/  put_unlocked_mapping_entry (struct address_space*,int,void*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radix_tree_exceptional_entry (void*) ; 
 int radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  unmap_mapping_pages (struct address_space*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *grab_mapping_entry(struct address_space *mapping, pgoff_t index,
		unsigned long size_flag)
{
	bool pmd_downgrade = false; /* splitting 2MiB entry into 4k entries? */
	void *entry, **slot;

restart:
	xa_lock_irq(&mapping->i_pages);
	entry = get_unlocked_mapping_entry(mapping, index, &slot);

	if (WARN_ON_ONCE(entry && !radix_tree_exceptional_entry(entry))) {
		entry = ERR_PTR(-EIO);
		goto out_unlock;
	}

	if (entry) {
		if (size_flag & RADIX_DAX_PMD) {
			if (dax_is_pte_entry(entry)) {
				put_unlocked_mapping_entry(mapping, index,
						entry);
				entry = ERR_PTR(-EEXIST);
				goto out_unlock;
			}
		} else { /* trying to grab a PTE entry */
			if (dax_is_pmd_entry(entry) &&
			    (dax_is_zero_entry(entry) ||
			     dax_is_empty_entry(entry))) {
				pmd_downgrade = true;
			}
		}
	}

	/* No entry for given index? Make sure radix tree is big enough. */
	if (!entry || pmd_downgrade) {
		int err;

		if (pmd_downgrade) {
			/*
			 * Make sure 'entry' remains valid while we drop
			 * the i_pages lock.
			 */
			entry = lock_slot(mapping, slot);
		}

		xa_unlock_irq(&mapping->i_pages);
		/*
		 * Besides huge zero pages the only other thing that gets
		 * downgraded are empty entries which don't need to be
		 * unmapped.
		 */
		if (pmd_downgrade && dax_is_zero_entry(entry))
			unmap_mapping_pages(mapping, index & ~PG_PMD_COLOUR,
							PG_PMD_NR, false);

		err = radix_tree_preload(
				mapping_gfp_mask(mapping) & ~__GFP_HIGHMEM);
		if (err) {
			if (pmd_downgrade)
				put_locked_mapping_entry(mapping, index);
			return ERR_PTR(err);
		}
		xa_lock_irq(&mapping->i_pages);

		if (!entry) {
			/*
			 * We needed to drop the i_pages lock while calling
			 * radix_tree_preload() and we didn't have an entry to
			 * lock.  See if another thread inserted an entry at
			 * our index during this time.
			 */
			entry = __radix_tree_lookup(&mapping->i_pages, index,
					NULL, &slot);
			if (entry) {
				radix_tree_preload_end();
				xa_unlock_irq(&mapping->i_pages);
				goto restart;
			}
		}

		if (pmd_downgrade) {
			dax_disassociate_entry(entry, mapping, false);
			radix_tree_delete(&mapping->i_pages, index);
			mapping->nrexceptional--;
			dax_wake_mapping_entry_waiter(mapping, index, entry,
					true);
		}

		entry = dax_radix_locked_entry(0, size_flag | RADIX_DAX_EMPTY);

		err = __radix_tree_insert(&mapping->i_pages, index,
				dax_radix_order(entry), entry);
		radix_tree_preload_end();
		if (err) {
			xa_unlock_irq(&mapping->i_pages);
			/*
			 * Our insertion of a DAX entry failed, most likely
			 * because we were inserting a PMD entry and it
			 * collided with a PTE sized entry at a different
			 * index in the PMD range.  We haven't inserted
			 * anything into the radix tree and have no waiters to
			 * wake.
			 */
			return ERR_PTR(err);
		}
		/* Good, we have inserted empty locked entry into the tree. */
		mapping->nrexceptional++;
		xa_unlock_irq(&mapping->i_pages);
		return entry;
	}
	entry = lock_slot(mapping, slot);
 out_unlock:
	xa_unlock_irq(&mapping->i_pages);
	return entry;
}