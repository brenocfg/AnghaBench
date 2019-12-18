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
struct page_vma_mapped_walk {int address; int /*<<< orphan*/ * pte; struct vm_area_struct* vma; struct page* page; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 scalar_t__ PAGE_SIZE ; 
 int PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageTransCompound (struct page*) ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mm_tlb_flush_pending (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,struct mm_struct*,int,scalar_t__) ; 
 int page_address_in_vma (struct page*,struct vm_area_struct*) ; 
 scalar_t__ page_count (struct page*) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  page_vma_mapped_walk (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  page_vma_mapped_walk_done (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  pte_clear_savedwrite (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkclean (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_protnone (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_savedwrite (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_clear_flush (struct vm_area_struct*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at_notify (struct mm_struct*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_protect_page(struct vm_area_struct *vma, struct page *page,
			      pte_t *orig_pte)
{
	struct mm_struct *mm = vma->vm_mm;
	struct page_vma_mapped_walk pvmw = {
		.page = page,
		.vma = vma,
	};
	int swapped;
	int err = -EFAULT;
	struct mmu_notifier_range range;

	pvmw.address = page_address_in_vma(page, vma);
	if (pvmw.address == -EFAULT)
		goto out;

	BUG_ON(PageTransCompound(page));

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm,
				pvmw.address,
				pvmw.address + PAGE_SIZE);
	mmu_notifier_invalidate_range_start(&range);

	if (!page_vma_mapped_walk(&pvmw))
		goto out_mn;
	if (WARN_ONCE(!pvmw.pte, "Unexpected PMD mapping?"))
		goto out_unlock;

	if (pte_write(*pvmw.pte) || pte_dirty(*pvmw.pte) ||
	    (pte_protnone(*pvmw.pte) && pte_savedwrite(*pvmw.pte)) ||
						mm_tlb_flush_pending(mm)) {
		pte_t entry;

		swapped = PageSwapCache(page);
		flush_cache_page(vma, pvmw.address, page_to_pfn(page));
		/*
		 * Ok this is tricky, when get_user_pages_fast() run it doesn't
		 * take any lock, therefore the check that we are going to make
		 * with the pagecount against the mapcount is racey and
		 * O_DIRECT can happen right after the check.
		 * So we clear the pte and flush the tlb before the check
		 * this assure us that no O_DIRECT can happen after the check
		 * or in the middle of the check.
		 *
		 * No need to notify as we are downgrading page table to read
		 * only not changing it to point to a new page.
		 *
		 * See Documentation/vm/mmu_notifier.rst
		 */
		entry = ptep_clear_flush(vma, pvmw.address, pvmw.pte);
		/*
		 * Check that no O_DIRECT or similar I/O is in progress on the
		 * page
		 */
		if (page_mapcount(page) + 1 + swapped != page_count(page)) {
			set_pte_at(mm, pvmw.address, pvmw.pte, entry);
			goto out_unlock;
		}
		if (pte_dirty(entry))
			set_page_dirty(page);

		if (pte_protnone(entry))
			entry = pte_mkclean(pte_clear_savedwrite(entry));
		else
			entry = pte_mkclean(pte_wrprotect(entry));
		set_pte_at_notify(mm, pvmw.address, pvmw.pte, entry);
	}
	*orig_pte = *pvmw.pte;
	err = 0;

out_unlock:
	page_vma_mapped_walk_done(&pvmw);
out_mn:
	mmu_notifier_invalidate_range_end(&range);
out:
	return err;
}