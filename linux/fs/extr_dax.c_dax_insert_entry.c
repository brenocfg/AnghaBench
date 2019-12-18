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
struct vm_fault {int /*<<< orphan*/  address; int /*<<< orphan*/  vma; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int DAX_LOCKED ; 
 unsigned long DAX_ZERO_PAGE ; 
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 unsigned long PG_PMD_COLOUR ; 
 int PG_PMD_NR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_associate_entry (void*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_disassociate_entry (void*,struct address_space*,int) ; 
 scalar_t__ dax_is_empty_entry (void*) ; 
 scalar_t__ dax_is_pmd_entry (void*) ; 
 scalar_t__ dax_is_zero_entry (void*) ; 
 void* dax_lock_entry (struct xa_state*,void*) ; 
 void* dax_make_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unmap_mapping_pages (struct address_space*,unsigned long,int,int) ; 
 void* xa_mk_value (int) ; 
 int xa_to_value (void*) ; 
 int /*<<< orphan*/  xas_load (struct xa_state*) ; 
 int /*<<< orphan*/  xas_lock_irq (struct xa_state*) ; 
 int /*<<< orphan*/  xas_reset (struct xa_state*) ; 
 int /*<<< orphan*/  xas_set_mark (struct xa_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_unlock_irq (struct xa_state*) ; 

__attribute__((used)) static void *dax_insert_entry(struct xa_state *xas,
		struct address_space *mapping, struct vm_fault *vmf,
		void *entry, pfn_t pfn, unsigned long flags, bool dirty)
{
	void *new_entry = dax_make_entry(pfn, flags);

	if (dirty)
		__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);

	if (dax_is_zero_entry(entry) && !(flags & DAX_ZERO_PAGE)) {
		unsigned long index = xas->xa_index;
		/* we are replacing a zero page with block mapping */
		if (dax_is_pmd_entry(entry))
			unmap_mapping_pages(mapping, index & ~PG_PMD_COLOUR,
					PG_PMD_NR, false);
		else /* pte entry */
			unmap_mapping_pages(mapping, index, 1, false);
	}

	xas_reset(xas);
	xas_lock_irq(xas);
	if (dax_is_zero_entry(entry) || dax_is_empty_entry(entry)) {
		void *old;

		dax_disassociate_entry(entry, mapping, false);
		dax_associate_entry(new_entry, mapping, vmf->vma, vmf->address);
		/*
		 * Only swap our new entry into the page cache if the current
		 * entry is a zero page or an empty entry.  If a normal PTE or
		 * PMD entry is already in the cache, we leave it alone.  This
		 * means that if we are trying to insert a PTE and the
		 * existing entry is a PMD, we will just leave the PMD in the
		 * tree and dirty it if necessary.
		 */
		old = dax_lock_entry(xas, new_entry);
		WARN_ON_ONCE(old != xa_mk_value(xa_to_value(entry) |
					DAX_LOCKED));
		entry = new_entry;
	} else {
		xas_load(xas);	/* Walk the xa_state */
	}

	if (dirty)
		xas_set_mark(xas, PAGECACHE_TAG_DIRTY);

	xas_unlock_irq(xas);
	return entry;
}