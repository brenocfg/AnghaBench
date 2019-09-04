#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  address; TYPE_2__* vma; int /*<<< orphan*/  pgoff; } ;
struct address_space {int /*<<< orphan*/  host; int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  enum page_entry_size { ____Placeholder_page_entry_size } page_entry_size ;
struct TYPE_4__ {TYPE_1__* vm_file; } ;
struct TYPE_3__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int PE_SIZE_PMD ; 
#define  PE_SIZE_PTE 128 
 int /*<<< orphan*/  VM_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  dax_is_pmd_entry (void*) ; 
 int /*<<< orphan*/  dax_is_pte_entry (void*) ; 
 void* get_unlocked_mapping_entry (struct address_space*,int /*<<< orphan*/ ,void***) ; 
 void* lock_slot (struct address_space*,void**) ; 
 int /*<<< orphan*/  put_locked_mapping_entry (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unlocked_mapping_entry (struct address_space*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dax_insert_pfn_mkwrite (int /*<<< orphan*/ ,struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dax_insert_pfn_mkwrite_no_entry (int /*<<< orphan*/ ,struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_mixed_mkwrite (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t dax_insert_pfn_mkwrite(struct vm_fault *vmf,
				  enum page_entry_size pe_size,
				  pfn_t pfn)
{
	struct address_space *mapping = vmf->vma->vm_file->f_mapping;
	void *entry, **slot;
	pgoff_t index = vmf->pgoff;
	vm_fault_t ret;

	xa_lock_irq(&mapping->i_pages);
	entry = get_unlocked_mapping_entry(mapping, index, &slot);
	/* Did we race with someone splitting entry or so? */
	if (!entry ||
	    (pe_size == PE_SIZE_PTE && !dax_is_pte_entry(entry)) ||
	    (pe_size == PE_SIZE_PMD && !dax_is_pmd_entry(entry))) {
		put_unlocked_mapping_entry(mapping, index, entry);
		xa_unlock_irq(&mapping->i_pages);
		trace_dax_insert_pfn_mkwrite_no_entry(mapping->host, vmf,
						      VM_FAULT_NOPAGE);
		return VM_FAULT_NOPAGE;
	}
	radix_tree_tag_set(&mapping->i_pages, index, PAGECACHE_TAG_DIRTY);
	entry = lock_slot(mapping, slot);
	xa_unlock_irq(&mapping->i_pages);
	switch (pe_size) {
	case PE_SIZE_PTE:
		ret = vmf_insert_mixed_mkwrite(vmf->vma, vmf->address, pfn);
		break;
#ifdef CONFIG_FS_DAX_PMD
	case PE_SIZE_PMD:
		ret = vmf_insert_pfn_pmd(vmf->vma, vmf->address, vmf->pmd,
			pfn, true);
		break;
#endif
	default:
		ret = VM_FAULT_FALLBACK;
	}
	put_locked_mapping_entry(mapping, index);
	trace_dax_insert_pfn_mkwrite(mapping->host, vmf, ret);
	return ret;
}