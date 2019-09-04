#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {TYPE_1__* vma; scalar_t__ pgoff; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int loff_t ;
typedef  enum page_entry_size { ____Placeholder_page_entry_size } page_entry_size ;
struct TYPE_2__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int PE_SIZE_PMD ; 
 int PE_SIZE_PTE ; 
 size_t PMD_SIZE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dax_insert_pfn_mkwrite (struct vm_fault*,int,int /*<<< orphan*/ ) ; 
 int vfs_fsync_range (int /*<<< orphan*/ ,int,int,int) ; 

vm_fault_t dax_finish_sync_fault(struct vm_fault *vmf,
		enum page_entry_size pe_size, pfn_t pfn)
{
	int err;
	loff_t start = ((loff_t)vmf->pgoff) << PAGE_SHIFT;
	size_t len = 0;

	if (pe_size == PE_SIZE_PTE)
		len = PAGE_SIZE;
	else if (pe_size == PE_SIZE_PMD)
		len = PMD_SIZE;
	else
		WARN_ON_ONCE(1);
	err = vfs_fsync_range(vmf->vma->vm_file, start, start + len - 1, 1);
	if (err)
		return VM_FAULT_SIGBUS;
	return dax_insert_pfn_mkwrite(vmf, pe_size, pfn);
}