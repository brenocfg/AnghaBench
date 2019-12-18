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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mmu_gather {int /*<<< orphan*/  mm; int /*<<< orphan*/  fullmm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/ * __pmd_trans_huge_lock (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 int /*<<< orphan*/  add_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ arch_needs_pgtable_deposit () ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_counter_file (struct page*) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,int) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_huge_get_and_clear_full (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swp_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ thp_migration_supported () ; 
 int /*<<< orphan*/  tlb_change_page_size (struct mmu_gather*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_remove_page_size (struct mmu_gather*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_remove_pmd_tlb_entry (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vma_is_dax (struct vm_area_struct*) ; 
 int /*<<< orphan*/  zap_deposited_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int zap_huge_pmd(struct mmu_gather *tlb, struct vm_area_struct *vma,
		 pmd_t *pmd, unsigned long addr)
{
	pmd_t orig_pmd;
	spinlock_t *ptl;

	tlb_change_page_size(tlb, HPAGE_PMD_SIZE);

	ptl = __pmd_trans_huge_lock(pmd, vma);
	if (!ptl)
		return 0;
	/*
	 * For architectures like ppc64 we look at deposited pgtable
	 * when calling pmdp_huge_get_and_clear. So do the
	 * pgtable_trans_huge_withdraw after finishing pmdp related
	 * operations.
	 */
	orig_pmd = pmdp_huge_get_and_clear_full(tlb->mm, addr, pmd,
			tlb->fullmm);
	tlb_remove_pmd_tlb_entry(tlb, pmd, addr);
	if (vma_is_dax(vma)) {
		if (arch_needs_pgtable_deposit())
			zap_deposited_table(tlb->mm, pmd);
		spin_unlock(ptl);
		if (is_huge_zero_pmd(orig_pmd))
			tlb_remove_page_size(tlb, pmd_page(orig_pmd), HPAGE_PMD_SIZE);
	} else if (is_huge_zero_pmd(orig_pmd)) {
		zap_deposited_table(tlb->mm, pmd);
		spin_unlock(ptl);
		tlb_remove_page_size(tlb, pmd_page(orig_pmd), HPAGE_PMD_SIZE);
	} else {
		struct page *page = NULL;
		int flush_needed = 1;

		if (pmd_present(orig_pmd)) {
			page = pmd_page(orig_pmd);
			page_remove_rmap(page, true);
			VM_BUG_ON_PAGE(page_mapcount(page) < 0, page);
			VM_BUG_ON_PAGE(!PageHead(page), page);
		} else if (thp_migration_supported()) {
			swp_entry_t entry;

			VM_BUG_ON(!is_pmd_migration_entry(orig_pmd));
			entry = pmd_to_swp_entry(orig_pmd);
			page = pfn_to_page(swp_offset(entry));
			flush_needed = 0;
		} else
			WARN_ONCE(1, "Non present huge pmd without pmd migration enabled!");

		if (PageAnon(page)) {
			zap_deposited_table(tlb->mm, pmd);
			add_mm_counter(tlb->mm, MM_ANONPAGES, -HPAGE_PMD_NR);
		} else {
			if (arch_needs_pgtable_deposit())
				zap_deposited_table(tlb->mm, pmd);
			add_mm_counter(tlb->mm, mm_counter_file(page), -HPAGE_PMD_NR);
		}

		spin_unlock(ptl);
		if (flush_needed)
			tlb_remove_page_size(tlb, page, HPAGE_PMD_SIZE);
	}
	return 1;
}