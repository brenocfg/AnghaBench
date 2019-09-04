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
typedef  int vm_flags_t ;
struct vm_operations_struct {scalar_t__ pfn_mkwrite; scalar_t__ page_mkwrite; } ;
struct vm_area_struct {int vm_flags; TYPE_1__* vm_file; struct vm_operations_struct* vm_ops; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_2__ {scalar_t__ f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MEM_SOFT_DIRTY ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int VM_PFNMAP ; 
 int VM_SHARED ; 
 int VM_SOFTDIRTY ; 
 int VM_WRITE ; 
 scalar_t__ mapping_cap_account_dirty (scalar_t__) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pgprot_modify (int /*<<< orphan*/ ,int) ; 

int vma_wants_writenotify(struct vm_area_struct *vma, pgprot_t vm_page_prot)
{
	vm_flags_t vm_flags = vma->vm_flags;
	const struct vm_operations_struct *vm_ops = vma->vm_ops;

	/* If it was private or non-writable, the write bit is already clear */
	if ((vm_flags & (VM_WRITE|VM_SHARED)) != ((VM_WRITE|VM_SHARED)))
		return 0;

	/* The backer wishes to know when pages are first written to? */
	if (vm_ops && (vm_ops->page_mkwrite || vm_ops->pfn_mkwrite))
		return 1;

	/* The open routine did something to the protections that pgprot_modify
	 * won't preserve? */
	if (pgprot_val(vm_page_prot) !=
	    pgprot_val(vm_pgprot_modify(vm_page_prot, vm_flags)))
		return 0;

	/* Do we need to track softdirty? */
	if (IS_ENABLED(CONFIG_MEM_SOFT_DIRTY) && !(vm_flags & VM_SOFTDIRTY))
		return 1;

	/* Specialty mapping? */
	if (vm_flags & VM_PFNMAP)
		return 0;

	/* Can the mapping track the dirty pages? */
	return vma->vm_file && vma->vm_file->f_mapping &&
		mapping_cap_account_dirty(vma->vm_file->f_mapping);
}