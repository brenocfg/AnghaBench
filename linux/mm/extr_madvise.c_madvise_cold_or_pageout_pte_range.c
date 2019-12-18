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
struct page {int /*<<< orphan*/  lru; } ;
struct mmu_gather {int /*<<< orphan*/  fullmm; struct mm_struct* mm; } ;
struct mm_walk {struct vm_area_struct* vma; struct madvise_walk_private* private; } ;
struct mm_struct {int dummy; } ;
struct madvise_walk_private {int pageout; struct mmu_gather* tlb; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReferenced (struct page*) ; 
 int EINTR ; 
 unsigned long HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (scalar_t__,struct page*) ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  deactivate_page (struct page*) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_batched_pending (struct mm_struct*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  page_list ; 
 int page_mapcount (struct page*) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pmd_mkold (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_trans_huge_lock (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_invalidate (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_get_and_clear_full (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  reclaim_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int split_huge_page (struct page*) ; 
 int /*<<< orphan*/  test_and_clear_page_young (struct page*) ; 
 scalar_t__ thp_migration_supported () ; 
 int /*<<< orphan*/  tlb_change_page_size (struct mmu_gather*,unsigned long) ; 
 int /*<<< orphan*/  tlb_remove_pmd_tlb_entry (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tlb_remove_tlb_entry (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int madvise_cold_or_pageout_pte_range(pmd_t *pmd,
				unsigned long addr, unsigned long end,
				struct mm_walk *walk)
{
	struct madvise_walk_private *private = walk->private;
	struct mmu_gather *tlb = private->tlb;
	bool pageout = private->pageout;
	struct mm_struct *mm = tlb->mm;
	struct vm_area_struct *vma = walk->vma;
	pte_t *orig_pte, *pte, ptent;
	spinlock_t *ptl;
	struct page *page = NULL;
	LIST_HEAD(page_list);

	if (fatal_signal_pending(current))
		return -EINTR;

#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	if (pmd_trans_huge(*pmd)) {
		pmd_t orig_pmd;
		unsigned long next = pmd_addr_end(addr, end);

		tlb_change_page_size(tlb, HPAGE_PMD_SIZE);
		ptl = pmd_trans_huge_lock(pmd, vma);
		if (!ptl)
			return 0;

		orig_pmd = *pmd;
		if (is_huge_zero_pmd(orig_pmd))
			goto huge_unlock;

		if (unlikely(!pmd_present(orig_pmd))) {
			VM_BUG_ON(thp_migration_supported() &&
					!is_pmd_migration_entry(orig_pmd));
			goto huge_unlock;
		}

		page = pmd_page(orig_pmd);
		if (next - addr != HPAGE_PMD_SIZE) {
			int err;

			if (page_mapcount(page) != 1)
				goto huge_unlock;

			get_page(page);
			spin_unlock(ptl);
			lock_page(page);
			err = split_huge_page(page);
			unlock_page(page);
			put_page(page);
			if (!err)
				goto regular_page;
			return 0;
		}

		if (pmd_young(orig_pmd)) {
			pmdp_invalidate(vma, addr, pmd);
			orig_pmd = pmd_mkold(orig_pmd);

			set_pmd_at(mm, addr, pmd, orig_pmd);
			tlb_remove_pmd_tlb_entry(tlb, pmd, addr);
		}

		ClearPageReferenced(page);
		test_and_clear_page_young(page);
		if (pageout) {
			if (!isolate_lru_page(page))
				list_add(&page->lru, &page_list);
		} else
			deactivate_page(page);
huge_unlock:
		spin_unlock(ptl);
		if (pageout)
			reclaim_pages(&page_list);
		return 0;
	}

	if (pmd_trans_unstable(pmd))
		return 0;
regular_page:
#endif
	tlb_change_page_size(tlb, PAGE_SIZE);
	orig_pte = pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	flush_tlb_batched_pending(mm);
	arch_enter_lazy_mmu_mode();
	for (; addr < end; pte++, addr += PAGE_SIZE) {
		ptent = *pte;

		if (pte_none(ptent))
			continue;

		if (!pte_present(ptent))
			continue;

		page = vm_normal_page(vma, addr, ptent);
		if (!page)
			continue;

		/*
		 * Creating a THP page is expensive so split it only if we
		 * are sure it's worth. Split it if we are only owner.
		 */
		if (PageTransCompound(page)) {
			if (page_mapcount(page) != 1)
				break;
			get_page(page);
			if (!trylock_page(page)) {
				put_page(page);
				break;
			}
			pte_unmap_unlock(orig_pte, ptl);
			if (split_huge_page(page)) {
				unlock_page(page);
				put_page(page);
				pte_offset_map_lock(mm, pmd, addr, &ptl);
				break;
			}
			unlock_page(page);
			put_page(page);
			pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
			pte--;
			addr -= PAGE_SIZE;
			continue;
		}

		VM_BUG_ON_PAGE(PageTransCompound(page), page);

		if (pte_young(ptent)) {
			ptent = ptep_get_and_clear_full(mm, addr, pte,
							tlb->fullmm);
			ptent = pte_mkold(ptent);
			set_pte_at(mm, addr, pte, ptent);
			tlb_remove_tlb_entry(tlb, pte, addr);
		}

		/*
		 * We are deactivating a page for accelerating reclaiming.
		 * VM couldn't reclaim the page unless we clear PG_young.
		 * As a side effect, it makes confuse idle-page tracking
		 * because they will miss recent referenced history.
		 */
		ClearPageReferenced(page);
		test_and_clear_page_young(page);
		if (pageout) {
			if (!isolate_lru_page(page))
				list_add(&page->lru, &page_list);
		} else
			deactivate_page(page);
	}

	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(orig_pte, ptl);
	if (pageout)
		reclaim_pages(&page_list);
	cond_resched();

	return 0;
}