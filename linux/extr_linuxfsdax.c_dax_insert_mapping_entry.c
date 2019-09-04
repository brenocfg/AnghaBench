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
struct vm_fault {int pgoff; int /*<<< orphan*/  address; int /*<<< orphan*/  vma; } ;
struct radix_tree_root {int dummy; } ;
struct radix_tree_node {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; struct radix_tree_root i_pages; } ;
typedef  int pgoff_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int PG_PMD_COLOUR ; 
 int PG_PMD_NR ; 
 unsigned long RADIX_DAX_ZERO_PAGE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __radix_tree_lookup (struct radix_tree_root*,int,struct radix_tree_node**,void***) ; 
 int /*<<< orphan*/  __radix_tree_replace (struct radix_tree_root*,struct radix_tree_node*,void**,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_associate_entry (void*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_disassociate_entry (void*,struct address_space*,int) ; 
 scalar_t__ dax_entry_size (void*) ; 
 scalar_t__ dax_is_empty_entry (void*) ; 
 scalar_t__ dax_is_pmd_entry (void*) ; 
 scalar_t__ dax_is_zero_entry (void*) ; 
 void* dax_radix_locked_entry (unsigned long,unsigned long) ; 
 unsigned long pfn_t_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_set (struct radix_tree_root*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_pages (struct address_space*,int,int,int) ; 
 int /*<<< orphan*/  xa_lock_irq (struct radix_tree_root*) ; 
 int /*<<< orphan*/  xa_unlock_irq (struct radix_tree_root*) ; 

__attribute__((used)) static void *dax_insert_mapping_entry(struct address_space *mapping,
				      struct vm_fault *vmf,
				      void *entry, pfn_t pfn_t,
				      unsigned long flags, bool dirty)
{
	struct radix_tree_root *pages = &mapping->i_pages;
	unsigned long pfn = pfn_t_to_pfn(pfn_t);
	pgoff_t index = vmf->pgoff;
	void *new_entry;

	if (dirty)
		__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);

	if (dax_is_zero_entry(entry) && !(flags & RADIX_DAX_ZERO_PAGE)) {
		/* we are replacing a zero page with block mapping */
		if (dax_is_pmd_entry(entry))
			unmap_mapping_pages(mapping, index & ~PG_PMD_COLOUR,
							PG_PMD_NR, false);
		else /* pte entry */
			unmap_mapping_pages(mapping, vmf->pgoff, 1, false);
	}

	xa_lock_irq(pages);
	new_entry = dax_radix_locked_entry(pfn, flags);
	if (dax_entry_size(entry) != dax_entry_size(new_entry)) {
		dax_disassociate_entry(entry, mapping, false);
		dax_associate_entry(new_entry, mapping, vmf->vma, vmf->address);
	}

	if (dax_is_zero_entry(entry) || dax_is_empty_entry(entry)) {
		/*
		 * Only swap our new entry into the radix tree if the current
		 * entry is a zero page or an empty entry.  If a normal PTE or
		 * PMD entry is already in the tree, we leave it alone.  This
		 * means that if we are trying to insert a PTE and the
		 * existing entry is a PMD, we will just leave the PMD in the
		 * tree and dirty it if necessary.
		 */
		struct radix_tree_node *node;
		void **slot;
		void *ret;

		ret = __radix_tree_lookup(pages, index, &node, &slot);
		WARN_ON_ONCE(ret != entry);
		__radix_tree_replace(pages, node, slot,
				     new_entry, NULL);
		entry = new_entry;
	}

	if (dirty)
		radix_tree_tag_set(pages, index, PAGECACHE_TAG_DIRTY);

	xa_unlock_irq(pages);
	return entry;
}