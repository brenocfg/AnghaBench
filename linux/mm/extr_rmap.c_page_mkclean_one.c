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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_end; } ;
struct page_vma_mapped_walk {unsigned long address; int /*<<< orphan*/ * pmd; int /*<<< orphan*/ * pte; int /*<<< orphan*/  flags; struct vm_area_struct* vma; struct page* page; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NOTIFY_PROTECTION_PAGE ; 
 int /*<<< orphan*/  PVMW_SYNC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ page_size (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ page_vma_mapped_walk (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  pmd_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkclean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_invalidate (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkclean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_clear_flush (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool page_mkclean_one(struct page *page, struct vm_area_struct *vma,
			    unsigned long address, void *arg)
{
	struct page_vma_mapped_walk pvmw = {
		.page = page,
		.vma = vma,
		.address = address,
		.flags = PVMW_SYNC,
	};
	struct mmu_notifier_range range;
	int *cleaned = arg;

	/*
	 * We have to assume the worse case ie pmd for invalidation. Note that
	 * the page can not be free from this function.
	 */
	mmu_notifier_range_init(&range, MMU_NOTIFY_PROTECTION_PAGE,
				0, vma, vma->vm_mm, address,
				min(vma->vm_end, address + page_size(page)));
	mmu_notifier_invalidate_range_start(&range);

	while (page_vma_mapped_walk(&pvmw)) {
		int ret = 0;

		address = pvmw.address;
		if (pvmw.pte) {
			pte_t entry;
			pte_t *pte = pvmw.pte;

			if (!pte_dirty(*pte) && !pte_write(*pte))
				continue;

			flush_cache_page(vma, address, pte_pfn(*pte));
			entry = ptep_clear_flush(vma, address, pte);
			entry = pte_wrprotect(entry);
			entry = pte_mkclean(entry);
			set_pte_at(vma->vm_mm, address, pte, entry);
			ret = 1;
		} else {
#ifdef CONFIG_TRANSPARENT_HUGE_PAGECACHE
			pmd_t *pmd = pvmw.pmd;
			pmd_t entry;

			if (!pmd_dirty(*pmd) && !pmd_write(*pmd))
				continue;

			flush_cache_page(vma, address, page_to_pfn(page));
			entry = pmdp_invalidate(vma, address, pmd);
			entry = pmd_wrprotect(entry);
			entry = pmd_mkclean(entry);
			set_pmd_at(vma->vm_mm, address, pmd, entry);
			ret = 1;
#else
			/* unexpected pmd-mapped page? */
			WARN_ON_ONCE(1);
#endif
		}

		/*
		 * No need to call mmu_notifier_invalidate_range() as we are
		 * downgrading page table protection not changing it to point
		 * to a new page.
		 *
		 * See Documentation/vm/mmu_notifier.rst
		 */
		if (ret)
			(*cleaned)++;
	}

	mmu_notifier_invalidate_range_end(&range);

	return true;
}