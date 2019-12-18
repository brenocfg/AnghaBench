#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_end; struct mm_struct* vm_mm; } ;
struct page_vma_mapped_walk {unsigned long address; int /*<<< orphan*/ * pte; struct vm_area_struct* vma; struct page* page; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {unsigned long start; scalar_t__ end; } ;
struct mm_struct {int /*<<< orphan*/  mmlist; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  enum ttu_flags { ____Placeholder_ttu_flags } ttu_flags ;
struct TYPE_8__ {int /*<<< orphan*/  mmlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MIGRATION ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  MM_SWAPENTS ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapBacked (struct page*) ; 
 int TTU_IGNORE_ACCESS ; 
 int TTU_IGNORE_HWPOISON ; 
 int TTU_IGNORE_MLOCK ; 
 int TTU_MIGRATION ; 
 int TTU_MUNLOCK ; 
 int TTU_SPLIT_FREEZE ; 
 int TTU_SPLIT_HUGE_PMD ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  adjust_range_if_pmd_sharing_possible (struct vm_area_struct*,unsigned long*,scalar_t__*) ; 
 scalar_t__ arch_unmap_one (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compound_nr (struct page*) ; 
 int /*<<< orphan*/  dec_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,struct page*) ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,scalar_t__) ; 
 scalar_t__ huge_pmd_unshare (struct mm_struct*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hugetlb_count_sub (int /*<<< orphan*/ ,struct mm_struct*) ; 
 int /*<<< orphan*/  inc_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 TYPE_6__ init_mm ; 
 int /*<<< orphan*/  is_device_private_page (struct page*) ; 
 scalar_t__ is_zone_device_page (struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__ make_hwpoison_entry (struct page*) ; 
 TYPE_1__ make_migration_entry (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlock_vma_page (struct page*) ; 
 int /*<<< orphan*/  mm_counter (struct page*) ; 
 int /*<<< orphan*/  mm_counter_file (struct page*) ; 
 int /*<<< orphan*/  mmlist_lock ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range (struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,scalar_t__) ; 
 scalar_t__ page_size (struct page*) ; 
 struct page* page_to_pfn (struct page*) ; 
 scalar_t__ page_vma_mapped_walk (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  page_vma_mapped_walk_done (struct page_vma_mapped_walk*) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 struct page* pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_soft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_swp_mksoft_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_unused (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_clear_flush (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ ptep_clear_flush_young_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptep_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_huge_swap_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_pmd_migration_entry (struct page_vma_mapped_walk*,struct page*) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tlb_ubc_flush_pending (struct mm_struct*,scalar_t__) ; 
 scalar_t__ should_defer_flush (struct mm_struct*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_pmd_address (struct vm_area_struct*,unsigned long,int,struct page*) ; 
 scalar_t__ swap_duplicate (TYPE_1__) ; 
 int /*<<< orphan*/  swp_entry_to_pte (TYPE_1__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_hiwater_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  userfaultfd_armed (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_mmu_pagesize (struct vm_area_struct*) ; 

__attribute__((used)) static bool try_to_unmap_one(struct page *page, struct vm_area_struct *vma,
		     unsigned long address, void *arg)
{
	struct mm_struct *mm = vma->vm_mm;
	struct page_vma_mapped_walk pvmw = {
		.page = page,
		.vma = vma,
		.address = address,
	};
	pte_t pteval;
	struct page *subpage;
	bool ret = true;
	struct mmu_notifier_range range;
	enum ttu_flags flags = (enum ttu_flags)arg;

	/* munlock has nothing to gain from examining un-locked vmas */
	if ((flags & TTU_MUNLOCK) && !(vma->vm_flags & VM_LOCKED))
		return true;

	if (IS_ENABLED(CONFIG_MIGRATION) && (flags & TTU_MIGRATION) &&
	    is_zone_device_page(page) && !is_device_private_page(page))
		return true;

	if (flags & TTU_SPLIT_HUGE_PMD) {
		split_huge_pmd_address(vma, address,
				flags & TTU_SPLIT_FREEZE, page);
	}

	/*
	 * For THP, we have to assume the worse case ie pmd for invalidation.
	 * For hugetlb, it could be much worse if we need to do pud
	 * invalidation in the case of pmd sharing.
	 *
	 * Note that the page can not be free in this function as call of
	 * try_to_unmap() must hold a reference on the page.
	 */
	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address,
				min(vma->vm_end, address + page_size(page)));
	if (PageHuge(page)) {
		/*
		 * If sharing is possible, start and end will be adjusted
		 * accordingly.
		 */
		adjust_range_if_pmd_sharing_possible(vma, &range.start,
						     &range.end);
	}
	mmu_notifier_invalidate_range_start(&range);

	while (page_vma_mapped_walk(&pvmw)) {
#ifdef CONFIG_ARCH_ENABLE_THP_MIGRATION
		/* PMD-mapped THP migration entry */
		if (!pvmw.pte && (flags & TTU_MIGRATION)) {
			VM_BUG_ON_PAGE(PageHuge(page) || !PageTransCompound(page), page);

			set_pmd_migration_entry(&pvmw, page);
			continue;
		}
#endif

		/*
		 * If the page is mlock()d, we cannot swap it out.
		 * If it's recently referenced (perhaps page_referenced
		 * skipped over this mm) then we should reactivate it.
		 */
		if (!(flags & TTU_IGNORE_MLOCK)) {
			if (vma->vm_flags & VM_LOCKED) {
				/* PTE-mapped THP are never mlocked */
				if (!PageTransCompound(page)) {
					/*
					 * Holding pte lock, we do *not* need
					 * mmap_sem here
					 */
					mlock_vma_page(page);
				}
				ret = false;
				page_vma_mapped_walk_done(&pvmw);
				break;
			}
			if (flags & TTU_MUNLOCK)
				continue;
		}

		/* Unexpected PMD-mapped THP? */
		VM_BUG_ON_PAGE(!pvmw.pte, page);

		subpage = page - page_to_pfn(page) + pte_pfn(*pvmw.pte);
		address = pvmw.address;

		if (PageHuge(page)) {
			if (huge_pmd_unshare(mm, &address, pvmw.pte)) {
				/*
				 * huge_pmd_unshare unmapped an entire PMD
				 * page.  There is no way of knowing exactly
				 * which PMDs may be cached for this mm, so
				 * we must flush them all.  start/end were
				 * already adjusted above to cover this range.
				 */
				flush_cache_range(vma, range.start, range.end);
				flush_tlb_range(vma, range.start, range.end);
				mmu_notifier_invalidate_range(mm, range.start,
							      range.end);

				/*
				 * The ref count of the PMD page was dropped
				 * which is part of the way map counting
				 * is done for shared PMDs.  Return 'true'
				 * here.  When there is no other sharing,
				 * huge_pmd_unshare returns false and we will
				 * unmap the actual page and drop map count
				 * to zero.
				 */
				page_vma_mapped_walk_done(&pvmw);
				break;
			}
		}

		if (IS_ENABLED(CONFIG_MIGRATION) &&
		    (flags & TTU_MIGRATION) &&
		    is_zone_device_page(page)) {
			swp_entry_t entry;
			pte_t swp_pte;

			pteval = ptep_get_and_clear(mm, pvmw.address, pvmw.pte);

			/*
			 * Store the pfn of the page in a special migration
			 * pte. do_swap_page() will wait until the migration
			 * pte is removed and then restart fault handling.
			 */
			entry = make_migration_entry(page, 0);
			swp_pte = swp_entry_to_pte(entry);
			if (pte_soft_dirty(pteval))
				swp_pte = pte_swp_mksoft_dirty(swp_pte);
			set_pte_at(mm, pvmw.address, pvmw.pte, swp_pte);
			/*
			 * No need to invalidate here it will synchronize on
			 * against the special swap migration pte.
			 *
			 * The assignment to subpage above was computed from a
			 * swap PTE which results in an invalid pointer.
			 * Since only PAGE_SIZE pages can currently be
			 * migrated, just set it to page. This will need to be
			 * changed when hugepage migrations to device private
			 * memory are supported.
			 */
			subpage = page;
			goto discard;
		}

		if (!(flags & TTU_IGNORE_ACCESS)) {
			if (ptep_clear_flush_young_notify(vma, address,
						pvmw.pte)) {
				ret = false;
				page_vma_mapped_walk_done(&pvmw);
				break;
			}
		}

		/* Nuke the page table entry. */
		flush_cache_page(vma, address, pte_pfn(*pvmw.pte));
		if (should_defer_flush(mm, flags)) {
			/*
			 * We clear the PTE but do not flush so potentially
			 * a remote CPU could still be writing to the page.
			 * If the entry was previously clean then the
			 * architecture must guarantee that a clear->dirty
			 * transition on a cached TLB entry is written through
			 * and traps if the PTE is unmapped.
			 */
			pteval = ptep_get_and_clear(mm, address, pvmw.pte);

			set_tlb_ubc_flush_pending(mm, pte_dirty(pteval));
		} else {
			pteval = ptep_clear_flush(vma, address, pvmw.pte);
		}

		/* Move the dirty bit to the page. Now the pte is gone. */
		if (pte_dirty(pteval))
			set_page_dirty(page);

		/* Update high watermark before we lower rss */
		update_hiwater_rss(mm);

		if (PageHWPoison(page) && !(flags & TTU_IGNORE_HWPOISON)) {
			pteval = swp_entry_to_pte(make_hwpoison_entry(subpage));
			if (PageHuge(page)) {
				hugetlb_count_sub(compound_nr(page), mm);
				set_huge_swap_pte_at(mm, address,
						     pvmw.pte, pteval,
						     vma_mmu_pagesize(vma));
			} else {
				dec_mm_counter(mm, mm_counter(page));
				set_pte_at(mm, address, pvmw.pte, pteval);
			}

		} else if (pte_unused(pteval) && !userfaultfd_armed(vma)) {
			/*
			 * The guest indicated that the page content is of no
			 * interest anymore. Simply discard the pte, vmscan
			 * will take care of the rest.
			 * A future reference will then fault in a new zero
			 * page. When userfaultfd is active, we must not drop
			 * this page though, as its main user (postcopy
			 * migration) will not expect userfaults on already
			 * copied pages.
			 */
			dec_mm_counter(mm, mm_counter(page));
			/* We have to invalidate as we cleared the pte */
			mmu_notifier_invalidate_range(mm, address,
						      address + PAGE_SIZE);
		} else if (IS_ENABLED(CONFIG_MIGRATION) &&
				(flags & (TTU_MIGRATION|TTU_SPLIT_FREEZE))) {
			swp_entry_t entry;
			pte_t swp_pte;

			if (arch_unmap_one(mm, vma, address, pteval) < 0) {
				set_pte_at(mm, address, pvmw.pte, pteval);
				ret = false;
				page_vma_mapped_walk_done(&pvmw);
				break;
			}

			/*
			 * Store the pfn of the page in a special migration
			 * pte. do_swap_page() will wait until the migration
			 * pte is removed and then restart fault handling.
			 */
			entry = make_migration_entry(subpage,
					pte_write(pteval));
			swp_pte = swp_entry_to_pte(entry);
			if (pte_soft_dirty(pteval))
				swp_pte = pte_swp_mksoft_dirty(swp_pte);
			set_pte_at(mm, address, pvmw.pte, swp_pte);
			/*
			 * No need to invalidate here it will synchronize on
			 * against the special swap migration pte.
			 */
		} else if (PageAnon(page)) {
			swp_entry_t entry = { .val = page_private(subpage) };
			pte_t swp_pte;
			/*
			 * Store the swap location in the pte.
			 * See handle_pte_fault() ...
			 */
			if (unlikely(PageSwapBacked(page) != PageSwapCache(page))) {
				WARN_ON_ONCE(1);
				ret = false;
				/* We have to invalidate as we cleared the pte */
				mmu_notifier_invalidate_range(mm, address,
							address + PAGE_SIZE);
				page_vma_mapped_walk_done(&pvmw);
				break;
			}

			/* MADV_FREE page check */
			if (!PageSwapBacked(page)) {
				if (!PageDirty(page)) {
					/* Invalidate as we cleared the pte */
					mmu_notifier_invalidate_range(mm,
						address, address + PAGE_SIZE);
					dec_mm_counter(mm, MM_ANONPAGES);
					goto discard;
				}

				/*
				 * If the page was redirtied, it cannot be
				 * discarded. Remap the page to page table.
				 */
				set_pte_at(mm, address, pvmw.pte, pteval);
				SetPageSwapBacked(page);
				ret = false;
				page_vma_mapped_walk_done(&pvmw);
				break;
			}

			if (swap_duplicate(entry) < 0) {
				set_pte_at(mm, address, pvmw.pte, pteval);
				ret = false;
				page_vma_mapped_walk_done(&pvmw);
				break;
			}
			if (arch_unmap_one(mm, vma, address, pteval) < 0) {
				set_pte_at(mm, address, pvmw.pte, pteval);
				ret = false;
				page_vma_mapped_walk_done(&pvmw);
				break;
			}
			if (list_empty(&mm->mmlist)) {
				spin_lock(&mmlist_lock);
				if (list_empty(&mm->mmlist))
					list_add(&mm->mmlist, &init_mm.mmlist);
				spin_unlock(&mmlist_lock);
			}
			dec_mm_counter(mm, MM_ANONPAGES);
			inc_mm_counter(mm, MM_SWAPENTS);
			swp_pte = swp_entry_to_pte(entry);
			if (pte_soft_dirty(pteval))
				swp_pte = pte_swp_mksoft_dirty(swp_pte);
			set_pte_at(mm, address, pvmw.pte, swp_pte);
			/* Invalidate as we cleared the pte */
			mmu_notifier_invalidate_range(mm, address,
						      address + PAGE_SIZE);
		} else {
			/*
			 * This is a locked file-backed page, thus it cannot
			 * be removed from the page cache and replaced by a new
			 * page before mmu_notifier_invalidate_range_end, so no
			 * concurrent thread might update its page table to
			 * point at new page while a device still is using this
			 * page.
			 *
			 * See Documentation/vm/mmu_notifier.rst
			 */
			dec_mm_counter(mm, mm_counter_file(page));
		}
discard:
		/*
		 * No need to call mmu_notifier_invalidate_range() it has be
		 * done above for all cases requiring it to happen under page
		 * table lock before mmu_notifier_invalidate_range_end()
		 *
		 * See Documentation/vm/mmu_notifier.rst
		 */
		page_remove_rmap(subpage, PageHuge(page));
		put_page(page);
	}

	mmu_notifier_invalidate_range_end(&range);

	return ret;
}