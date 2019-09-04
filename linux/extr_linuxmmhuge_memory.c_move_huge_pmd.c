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
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_MASK ; 
 unsigned long HPAGE_PMD_SIZE ; 
 scalar_t__ PMD_SIZE ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/ * __pmd_trans_huge_lock (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  move_soft_dirty_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgtable_trans_huge_deposit (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgtable_trans_huge_withdraw (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_move_must_withdraw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_huge_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool move_huge_pmd(struct vm_area_struct *vma, unsigned long old_addr,
		  unsigned long new_addr, unsigned long old_end,
		  pmd_t *old_pmd, pmd_t *new_pmd)
{
	spinlock_t *old_ptl, *new_ptl;
	pmd_t pmd;
	struct mm_struct *mm = vma->vm_mm;
	bool force_flush = false;

	if ((old_addr & ~HPAGE_PMD_MASK) ||
	    (new_addr & ~HPAGE_PMD_MASK) ||
	    old_end - old_addr < HPAGE_PMD_SIZE)
		return false;

	/*
	 * The destination pmd shouldn't be established, free_pgtables()
	 * should have release it.
	 */
	if (WARN_ON(!pmd_none(*new_pmd))) {
		VM_BUG_ON(pmd_trans_huge(*new_pmd));
		return false;
	}

	/*
	 * We don't have to worry about the ordering of src and dst
	 * ptlocks because exclusive mmap_sem prevents deadlock.
	 */
	old_ptl = __pmd_trans_huge_lock(old_pmd, vma);
	if (old_ptl) {
		new_ptl = pmd_lockptr(mm, new_pmd);
		if (new_ptl != old_ptl)
			spin_lock_nested(new_ptl, SINGLE_DEPTH_NESTING);
		pmd = pmdp_huge_get_and_clear(mm, old_addr, old_pmd);
		if (pmd_present(pmd))
			force_flush = true;
		VM_BUG_ON(!pmd_none(*new_pmd));

		if (pmd_move_must_withdraw(new_ptl, old_ptl, vma)) {
			pgtable_t pgtable;
			pgtable = pgtable_trans_huge_withdraw(mm, old_pmd);
			pgtable_trans_huge_deposit(mm, new_pmd, pgtable);
		}
		pmd = move_soft_dirty_pmd(pmd);
		set_pmd_at(mm, new_addr, new_pmd, pmd);
		if (force_flush)
			flush_tlb_range(vma, old_addr, old_addr + PMD_SIZE);
		if (new_ptl != old_ptl)
			spin_unlock(new_ptl);
		spin_unlock(old_ptl);
		return true;
	}
	return false;
}