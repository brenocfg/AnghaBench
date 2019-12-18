#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {int flags; unsigned long address; int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pmd; TYPE_1__* vma; } ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_3__ {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int FAULT_FLAG_WRITE ; 
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pmdp_set_access_flags (TYPE_1__*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_mmu_cache_pmd (TYPE_1__*,unsigned long,int /*<<< orphan*/ *) ; 

void huge_pmd_set_accessed(struct vm_fault *vmf, pmd_t orig_pmd)
{
	pmd_t entry;
	unsigned long haddr;
	bool write = vmf->flags & FAULT_FLAG_WRITE;

	vmf->ptl = pmd_lock(vmf->vma->vm_mm, vmf->pmd);
	if (unlikely(!pmd_same(*vmf->pmd, orig_pmd)))
		goto unlock;

	entry = pmd_mkyoung(orig_pmd);
	if (write)
		entry = pmd_mkdirty(entry);
	haddr = vmf->address & HPAGE_PMD_MASK;
	if (pmdp_set_access_flags(vmf->vma, haddr, vmf->pmd, entry, write))
		update_mmu_cache_pmd(vmf->vma, vmf->address, vmf->pmd);

unlock:
	spin_unlock(vmf->ptl);
}