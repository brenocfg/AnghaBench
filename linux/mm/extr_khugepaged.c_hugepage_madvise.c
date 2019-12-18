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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int ENOMEM ; 
#define  MADV_HUGEPAGE 129 
#define  MADV_NOHUGEPAGE 128 
 unsigned long VM_HUGEPAGE ; 
 unsigned long VM_NOHUGEPAGE ; 
 unsigned long VM_NO_KHUGEPAGED ; 
 int /*<<< orphan*/  khugepaged_enter_vma_merge (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  mm_has_pgste (int /*<<< orphan*/ ) ; 

int hugepage_madvise(struct vm_area_struct *vma,
		     unsigned long *vm_flags, int advice)
{
	switch (advice) {
	case MADV_HUGEPAGE:
#ifdef CONFIG_S390
		/*
		 * qemu blindly sets MADV_HUGEPAGE on all allocations, but s390
		 * can't handle this properly after s390_enable_sie, so we simply
		 * ignore the madvise to prevent qemu from causing a SIGSEGV.
		 */
		if (mm_has_pgste(vma->vm_mm))
			return 0;
#endif
		*vm_flags &= ~VM_NOHUGEPAGE;
		*vm_flags |= VM_HUGEPAGE;
		/*
		 * If the vma become good for khugepaged to scan,
		 * register it here without waiting a page fault that
		 * may not happen any time soon.
		 */
		if (!(*vm_flags & VM_NO_KHUGEPAGED) &&
				khugepaged_enter_vma_merge(vma, *vm_flags))
			return -ENOMEM;
		break;
	case MADV_NOHUGEPAGE:
		*vm_flags &= ~VM_HUGEPAGE;
		*vm_flags |= VM_NOHUGEPAGE;
		/*
		 * Setting VM_NOHUGEPAGE will prevent khugepaged from scanning
		 * this vma even if we leave the mm registered in khugepaged if
		 * it got registered before VM_NOHUGEPAGE was set.
		 */
		break;
	}

	return 0;
}