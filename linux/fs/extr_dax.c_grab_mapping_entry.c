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
struct xa_state {unsigned long xa_index; scalar_t__ xa_node; } ;
struct address_space {int /*<<< orphan*/  nrexceptional; } ;

/* Variables and functions */
 unsigned long DAX_EMPTY ; 
 unsigned long DAX_PMD ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PG_PMD_COLOUR ; 
 int /*<<< orphan*/  PG_PMD_NR ; 
 int /*<<< orphan*/  VM_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 scalar_t__ XA_ERROR (int /*<<< orphan*/ ) ; 
 int __GFP_HIGHMEM ; 
 int /*<<< orphan*/  dax_disassociate_entry (void*,struct address_space*,int) ; 
 scalar_t__ dax_is_conflict (void*) ; 
 scalar_t__ dax_is_empty_entry (void*) ; 
 scalar_t__ dax_is_pmd_entry (void*) ; 
 scalar_t__ dax_is_zero_entry (void*) ; 
 int /*<<< orphan*/  dax_lock_entry (struct xa_state*,void*) ; 
 void* dax_make_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dax_wake_entry (struct xa_state*,void*,int) ; 
 void* get_unlocked_entry (struct xa_state*,unsigned int) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  pfn_to_pfn_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_pages (struct address_space*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xa_is_value (void*) ; 
 void* xa_mk_internal (int /*<<< orphan*/ ) ; 
 scalar_t__ xas_error (struct xa_state*) ; 
 int /*<<< orphan*/  xas_lock_irq (struct xa_state*) ; 
 scalar_t__ xas_nomem (struct xa_state*,int) ; 
 int /*<<< orphan*/  xas_reset (struct xa_state*) ; 
 int /*<<< orphan*/  xas_set (struct xa_state*,unsigned long) ; 
 int /*<<< orphan*/  xas_set_err (struct xa_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (struct xa_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_unlock_irq (struct xa_state*) ; 

__attribute__((used)) static void *grab_mapping_entry(struct xa_state *xas,
		struct address_space *mapping, unsigned int order)
{
	unsigned long index = xas->xa_index;
	bool pmd_downgrade = false; /* splitting PMD entry into PTE entries? */
	void *entry;

retry:
	xas_lock_irq(xas);
	entry = get_unlocked_entry(xas, order);

	if (entry) {
		if (dax_is_conflict(entry))
			goto fallback;
		if (!xa_is_value(entry)) {
			xas_set_err(xas, EIO);
			goto out_unlock;
		}

		if (order == 0) {
			if (dax_is_pmd_entry(entry) &&
			    (dax_is_zero_entry(entry) ||
			     dax_is_empty_entry(entry))) {
				pmd_downgrade = true;
			}
		}
	}

	if (pmd_downgrade) {
		/*
		 * Make sure 'entry' remains valid while we drop
		 * the i_pages lock.
		 */
		dax_lock_entry(xas, entry);

		/*
		 * Besides huge zero pages the only other thing that gets
		 * downgraded are empty entries which don't need to be
		 * unmapped.
		 */
		if (dax_is_zero_entry(entry)) {
			xas_unlock_irq(xas);
			unmap_mapping_pages(mapping,
					xas->xa_index & ~PG_PMD_COLOUR,
					PG_PMD_NR, false);
			xas_reset(xas);
			xas_lock_irq(xas);
		}

		dax_disassociate_entry(entry, mapping, false);
		xas_store(xas, NULL);	/* undo the PMD join */
		dax_wake_entry(xas, entry, true);
		mapping->nrexceptional--;
		entry = NULL;
		xas_set(xas, index);
	}

	if (entry) {
		dax_lock_entry(xas, entry);
	} else {
		unsigned long flags = DAX_EMPTY;

		if (order > 0)
			flags |= DAX_PMD;
		entry = dax_make_entry(pfn_to_pfn_t(0), flags);
		dax_lock_entry(xas, entry);
		if (xas_error(xas))
			goto out_unlock;
		mapping->nrexceptional++;
	}

out_unlock:
	xas_unlock_irq(xas);
	if (xas_nomem(xas, mapping_gfp_mask(mapping) & ~__GFP_HIGHMEM))
		goto retry;
	if (xas->xa_node == XA_ERROR(-ENOMEM))
		return xa_mk_internal(VM_FAULT_OOM);
	if (xas_error(xas))
		return xa_mk_internal(VM_FAULT_SIGBUS);
	return entry;
fallback:
	xas_unlock_irq(xas);
	return xa_mk_internal(VM_FAULT_FALLBACK);
}