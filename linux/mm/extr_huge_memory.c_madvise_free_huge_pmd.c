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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mmu_gather {struct mm_struct* mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 unsigned long HPAGE_PMD_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_lazyfree (struct page*) ; 
 int page_mapcount (struct page*) ; 
 scalar_t__ pmd_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkclean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkold (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_trans_huge_lock (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 scalar_t__ pmd_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_invalidate (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 scalar_t__ thp_migration_supported () ; 
 int /*<<< orphan*/  tlb_change_page_size (struct mmu_gather*,unsigned long) ; 
 int /*<<< orphan*/  tlb_remove_pmd_tlb_entry (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

bool madvise_free_huge_pmd(struct mmu_gather *tlb, struct vm_area_struct *vma,
		pmd_t *pmd, unsigned long addr, unsigned long next)
{
	spinlock_t *ptl;
	pmd_t orig_pmd;
	struct page *page;
	struct mm_struct *mm = tlb->mm;
	bool ret = false;

	tlb_change_page_size(tlb, HPAGE_PMD_SIZE);

	ptl = pmd_trans_huge_lock(pmd, vma);
	if (!ptl)
		goto out_unlocked;

	orig_pmd = *pmd;
	if (is_huge_zero_pmd(orig_pmd))
		goto out;

	if (unlikely(!pmd_present(orig_pmd))) {
		VM_BUG_ON(thp_migration_supported() &&
				  !is_pmd_migration_entry(orig_pmd));
		goto out;
	}

	page = pmd_page(orig_pmd);
	/*
	 * If other processes are mapping this page, we couldn't discard
	 * the page unless they all do MADV_FREE so let's skip the page.
	 */
	if (page_mapcount(page) != 1)
		goto out;

	if (!trylock_page(page))
		goto out;

	/*
	 * If user want to discard part-pages of THP, split it so MADV_FREE
	 * will deactivate only them.
	 */
	if (next - addr != HPAGE_PMD_SIZE) {
		get_page(page);
		spin_unlock(ptl);
		split_huge_page(page);
		unlock_page(page);
		put_page(page);
		goto out_unlocked;
	}

	if (PageDirty(page))
		ClearPageDirty(page);
	unlock_page(page);

	if (pmd_young(orig_pmd) || pmd_dirty(orig_pmd)) {
		pmdp_invalidate(vma, addr, pmd);
		orig_pmd = pmd_mkold(orig_pmd);
		orig_pmd = pmd_mkclean(orig_pmd);

		set_pmd_at(mm, addr, pmd, orig_pmd);
		tlb_remove_pmd_tlb_entry(tlb, pmd, addr);
	}

	mark_page_lazyfree(page);
	ret = true;
out:
	spin_unlock(ptl);
out_unlocked:
	return ret;
}