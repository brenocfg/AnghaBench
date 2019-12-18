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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mmu_gather {int /*<<< orphan*/  fullmm; struct mm_struct* mm; } ;
struct mm_walk {struct vm_area_struct* vma; struct mmu_gather* private; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  MM_SWAPENTS ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (scalar_t__,struct page*) ; 
 int /*<<< orphan*/  add_mm_counter (struct mm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_batched_pending (struct mm_struct*) ; 
 int /*<<< orphan*/  free_swap_and_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ madvise_free_huge_pmd (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mark_page_lazyfree (struct page*) ; 
 scalar_t__ non_swap_entry (int /*<<< orphan*/ ) ; 
 int page_mapcount (struct page*) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_clear_not_present_full (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkclean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_get_and_clear_full (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ split_huge_page (struct page*) ; 
 int /*<<< orphan*/  sync_mm_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  tlb_change_page_size (struct mmu_gather*,scalar_t__) ; 
 int /*<<< orphan*/  tlb_remove_tlb_entry (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_to_free_swap (struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int madvise_free_pte_range(pmd_t *pmd, unsigned long addr,
				unsigned long end, struct mm_walk *walk)

{
	struct mmu_gather *tlb = walk->private;
	struct mm_struct *mm = tlb->mm;
	struct vm_area_struct *vma = walk->vma;
	spinlock_t *ptl;
	pte_t *orig_pte, *pte, ptent;
	struct page *page;
	int nr_swap = 0;
	unsigned long next;

	next = pmd_addr_end(addr, end);
	if (pmd_trans_huge(*pmd))
		if (madvise_free_huge_pmd(tlb, vma, pmd, addr, next))
			goto next;

	if (pmd_trans_unstable(pmd))
		return 0;

	tlb_change_page_size(tlb, PAGE_SIZE);
	orig_pte = pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
	flush_tlb_batched_pending(mm);
	arch_enter_lazy_mmu_mode();
	for (; addr != end; pte++, addr += PAGE_SIZE) {
		ptent = *pte;

		if (pte_none(ptent))
			continue;
		/*
		 * If the pte has swp_entry, just clear page table to
		 * prevent swap-in which is more expensive rather than
		 * (page allocation + zeroing).
		 */
		if (!pte_present(ptent)) {
			swp_entry_t entry;

			entry = pte_to_swp_entry(ptent);
			if (non_swap_entry(entry))
				continue;
			nr_swap--;
			free_swap_and_cache(entry);
			pte_clear_not_present_full(mm, addr, pte, tlb->fullmm);
			continue;
		}

		page = vm_normal_page(vma, addr, ptent);
		if (!page)
			continue;

		/*
		 * If pmd isn't transhuge but the page is THP and
		 * is owned by only this process, split it and
		 * deactivate all pages.
		 */
		if (PageTransCompound(page)) {
			if (page_mapcount(page) != 1)
				goto out;
			get_page(page);
			if (!trylock_page(page)) {
				put_page(page);
				goto out;
			}
			pte_unmap_unlock(orig_pte, ptl);
			if (split_huge_page(page)) {
				unlock_page(page);
				put_page(page);
				pte_offset_map_lock(mm, pmd, addr, &ptl);
				goto out;
			}
			unlock_page(page);
			put_page(page);
			pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
			pte--;
			addr -= PAGE_SIZE;
			continue;
		}

		VM_BUG_ON_PAGE(PageTransCompound(page), page);

		if (PageSwapCache(page) || PageDirty(page)) {
			if (!trylock_page(page))
				continue;
			/*
			 * If page is shared with others, we couldn't clear
			 * PG_dirty of the page.
			 */
			if (page_mapcount(page) != 1) {
				unlock_page(page);
				continue;
			}

			if (PageSwapCache(page) && !try_to_free_swap(page)) {
				unlock_page(page);
				continue;
			}

			ClearPageDirty(page);
			unlock_page(page);
		}

		if (pte_young(ptent) || pte_dirty(ptent)) {
			/*
			 * Some of architecture(ex, PPC) don't update TLB
			 * with set_pte_at and tlb_remove_tlb_entry so for
			 * the portability, remap the pte with old|clean
			 * after pte clearing.
			 */
			ptent = ptep_get_and_clear_full(mm, addr, pte,
							tlb->fullmm);

			ptent = pte_mkold(ptent);
			ptent = pte_mkclean(ptent);
			set_pte_at(mm, addr, pte, ptent);
			tlb_remove_tlb_entry(tlb, pte, addr);
		}
		mark_page_lazyfree(page);
	}
out:
	if (nr_swap) {
		if (current->mm == mm)
			sync_mm_rss(mm);

		add_mm_counter(mm, MM_SWAPENTS, nr_swap);
	}
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(orig_pte, ptl);
	cond_resched();
next:
	return 0;
}