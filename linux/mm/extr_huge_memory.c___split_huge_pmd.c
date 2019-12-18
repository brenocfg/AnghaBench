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
struct page {int dummy; } ;
struct mmu_notifier_range {int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_MASK ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 scalar_t__ PageMlocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __split_huge_pmd_locked (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_page_mlock (struct page*) ; 
 scalar_t__ is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_only_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __split_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long address, bool freeze, struct page *page)
{
	spinlock_t *ptl;
	struct mmu_notifier_range range;

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address & HPAGE_PMD_MASK,
				(address & HPAGE_PMD_MASK) + HPAGE_PMD_SIZE);
	mmu_notifier_invalidate_range_start(&range);
	ptl = pmd_lock(vma->vm_mm, pmd);

	/*
	 * If caller asks to setup a migration entries, we need a page to check
	 * pmd against. Otherwise we can end up replacing wrong page.
	 */
	VM_BUG_ON(freeze && !page);
	if (page && page != pmd_page(*pmd))
	        goto out;

	if (pmd_trans_huge(*pmd)) {
		page = pmd_page(*pmd);
		if (PageMlocked(page))
			clear_page_mlock(page);
	} else if (!(pmd_devmap(*pmd) || is_pmd_migration_entry(*pmd)))
		goto out;
	__split_huge_pmd_locked(vma, pmd, range.start, freeze);
out:
	spin_unlock(ptl);
	/*
	 * No need to double call mmu_notifier->invalidate_range() callback.
	 * They are 3 cases to consider inside __split_huge_pmd_locked():
	 *  1) pmdp_huge_clear_flush_notify() call invalidate_range() obvious
	 *  2) __split_huge_zero_page_pmd() read only zero page and any write
	 *    fault will trigger a flush_notify before pointing to a new page
	 *    (it is fine if the secondary mmu keeps pointing to the old zero
	 *    page in the meantime)
	 *  3) Split a huge pmd into pte pointing to the same page. No need
	 *     to invalidate secondary tlb entry they are all still valid.
	 *     any further changes to individual pte will notify. So no need
	 *     to call mmu_notifier->invalidate_range()
	 */
	mmu_notifier_invalidate_range_only_end(&range);
}