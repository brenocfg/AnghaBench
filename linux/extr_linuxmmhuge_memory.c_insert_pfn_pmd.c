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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/ * pgtable_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_pmd_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mm_inc_nr_ptes (struct mm_struct*) ; 
 scalar_t__ pfn_t_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_t_pmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_t_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgtable_trans_huge_deposit (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkdevmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pmdp_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_mmu_cache_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_pfn_pmd(struct vm_area_struct *vma, unsigned long addr,
		pmd_t *pmd, pfn_t pfn, pgprot_t prot, bool write,
		pgtable_t pgtable)
{
	struct mm_struct *mm = vma->vm_mm;
	pmd_t entry;
	spinlock_t *ptl;

	ptl = pmd_lock(mm, pmd);
	if (!pmd_none(*pmd)) {
		if (write) {
			if (pmd_pfn(*pmd) != pfn_t_to_pfn(pfn)) {
				WARN_ON_ONCE(!is_huge_zero_pmd(*pmd));
				goto out_unlock;
			}
			entry = pmd_mkyoung(*pmd);
			entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
			if (pmdp_set_access_flags(vma, addr, pmd, entry, 1))
				update_mmu_cache_pmd(vma, addr, pmd);
		}

		goto out_unlock;
	}

	entry = pmd_mkhuge(pfn_t_pmd(pfn, prot));
	if (pfn_t_devmap(pfn))
		entry = pmd_mkdevmap(entry);
	if (write) {
		entry = pmd_mkyoung(pmd_mkdirty(entry));
		entry = maybe_pmd_mkwrite(entry, vma);
	}

	if (pgtable) {
		pgtable_trans_huge_deposit(mm, pmd, pgtable);
		mm_inc_nr_ptes(mm);
		pgtable = NULL;
	}

	set_pmd_at(mm, addr, pmd, entry);
	update_mmu_cache_pmd(vma, addr, pmd);

out_unlock:
	spin_unlock(ptl);
	if (pgtable)
		pte_free(mm, pgtable);
}