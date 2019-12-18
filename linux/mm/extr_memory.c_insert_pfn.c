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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * get_locked_pte (struct mm_struct*,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  is_zero_pfn (scalar_t__) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 scalar_t__ pfn_t_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_t_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_t_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdevmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkspecial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ptep_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t insert_pfn(struct vm_area_struct *vma, unsigned long addr,
			pfn_t pfn, pgprot_t prot, bool mkwrite)
{
	struct mm_struct *mm = vma->vm_mm;
	pte_t *pte, entry;
	spinlock_t *ptl;

	pte = get_locked_pte(mm, addr, &ptl);
	if (!pte)
		return VM_FAULT_OOM;
	if (!pte_none(*pte)) {
		if (mkwrite) {
			/*
			 * For read faults on private mappings the PFN passed
			 * in may not match the PFN we have mapped if the
			 * mapped PFN is a writeable COW page.  In the mkwrite
			 * case we are creating a writable PTE for a shared
			 * mapping and we expect the PFNs to match. If they
			 * don't match, we are likely racing with block
			 * allocation and mapping invalidation so just skip the
			 * update.
			 */
			if (pte_pfn(*pte) != pfn_t_to_pfn(pfn)) {
				WARN_ON_ONCE(!is_zero_pfn(pte_pfn(*pte)));
				goto out_unlock;
			}
			entry = pte_mkyoung(*pte);
			entry = maybe_mkwrite(pte_mkdirty(entry), vma);
			if (ptep_set_access_flags(vma, addr, pte, entry, 1))
				update_mmu_cache(vma, addr, pte);
		}
		goto out_unlock;
	}

	/* Ok, finally just insert the thing.. */
	if (pfn_t_devmap(pfn))
		entry = pte_mkdevmap(pfn_t_pte(pfn, prot));
	else
		entry = pte_mkspecial(pfn_t_pte(pfn, prot));

	if (mkwrite) {
		entry = pte_mkyoung(entry);
		entry = maybe_mkwrite(pte_mkdirty(entry), vma);
	}

	set_pte_at(mm, addr, pte, entry);
	update_mmu_cache(vma, addr, pte); /* XXX: why not for insert_page? */

out_unlock:
	pte_unmap_unlock(pte, ptl);
	return VM_FAULT_NOPAGE;
}