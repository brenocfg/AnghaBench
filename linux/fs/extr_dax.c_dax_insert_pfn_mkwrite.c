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
typedef  int /*<<< orphan*/  pfn_t ;
struct TYPE_4__ {TYPE_1__* vm_file; } ;
struct TYPE_3__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 unsigned int PMD_ORDER ; 
 int /*<<< orphan*/  VM_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  XA_STATE_ORDER (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ dax_is_conflict (void*) ; 
 int /*<<< orphan*/  dax_is_pte_entry (void*) ; 
 int /*<<< orphan*/  dax_lock_entry (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dax_unlock_entry (int /*<<< orphan*/ *,void*) ; 
 void* get_unlocked_entry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  put_unlocked_entry (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  trace_dax_insert_pfn_mkwrite (int /*<<< orphan*/ ,struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dax_insert_pfn_mkwrite_no_entry (int /*<<< orphan*/ ,struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_mixed_mkwrite (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_pfn_pmd (struct vm_fault*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas ; 
 int /*<<< orphan*/  xas_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t
dax_insert_pfn_mkwrite(struct vm_fault *vmf, pfn_t pfn, unsigned int order)
{
	struct address_space *mapping = vmf->vma->vm_file->f_mapping;
	XA_STATE_ORDER(xas, &mapping->i_pages, vmf->pgoff, order);
	void *entry;
	vm_fault_t ret;

	xas_lock_irq(&xas);
	entry = get_unlocked_entry(&xas, order);
	/* Did we race with someone splitting entry or so? */
	if (!entry || dax_is_conflict(entry) ||
	    (order == 0 && !dax_is_pte_entry(entry))) {
		put_unlocked_entry(&xas, entry);
		xas_unlock_irq(&xas);
		trace_dax_insert_pfn_mkwrite_no_entry(mapping->host, vmf,
						      VM_FAULT_NOPAGE);
		return VM_FAULT_NOPAGE;
	}
	xas_set_mark(&xas, PAGECACHE_TAG_DIRTY);
	dax_lock_entry(&xas, entry);
	xas_unlock_irq(&xas);
	if (order == 0)
		ret = vmf_insert_mixed_mkwrite(vmf->vma, vmf->address, pfn);
#ifdef CONFIG_FS_DAX_PMD
	else if (order == PMD_ORDER)
		ret = vmf_insert_pfn_pmd(vmf, pfn, FAULT_FLAG_WRITE);
#endif
	else
		ret = VM_FAULT_FALLBACK;
	dax_unlock_entry(&xas, entry);
	trace_dax_insert_pfn_mkwrite(mapping->host, vmf, ret);
	return ret;
}