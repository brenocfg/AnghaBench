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
struct page_vma_mapped_walk {int address; int flags; int /*<<< orphan*/ * ptl; int /*<<< orphan*/ * pmd; int /*<<< orphan*/ * pte; struct page* page; TYPE_1__* vma; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;
struct TYPE_2__ {int vm_end; struct mm_struct* vm_mm; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int PMD_SIZE ; 
 int PVMW_MIGRATION ; 
 scalar_t__ PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int __vma_address (struct page*,TYPE_1__*) ; 
 scalar_t__ check_pte (struct page_vma_mapped_walk*) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/ * huge_pte_lockptr (int /*<<< orphan*/ ,struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  map_pte (struct page_vma_mapped_walk*) ; 
 struct page* migration_entry_to_page (int /*<<< orphan*/ ) ; 
 int not_found (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_hstate (struct page*) ; 
 int /*<<< orphan*/  page_size (struct page*) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,int) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_to_swp_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ thp_migration_supported () ; 
 scalar_t__ unlikely (scalar_t__) ; 

bool page_vma_mapped_walk(struct page_vma_mapped_walk *pvmw)
{
	struct mm_struct *mm = pvmw->vma->vm_mm;
	struct page *page = pvmw->page;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t pmde;

	/* The only possible pmd mapping has been handled on last iteration */
	if (pvmw->pmd && !pvmw->pte)
		return not_found(pvmw);

	if (pvmw->pte)
		goto next_pte;

	if (unlikely(PageHuge(pvmw->page))) {
		/* when pud is not present, pte will be NULL */
		pvmw->pte = huge_pte_offset(mm, pvmw->address, page_size(page));
		if (!pvmw->pte)
			return false;

		pvmw->ptl = huge_pte_lockptr(page_hstate(page), mm, pvmw->pte);
		spin_lock(pvmw->ptl);
		if (!check_pte(pvmw))
			return not_found(pvmw);
		return true;
	}
restart:
	pgd = pgd_offset(mm, pvmw->address);
	if (!pgd_present(*pgd))
		return false;
	p4d = p4d_offset(pgd, pvmw->address);
	if (!p4d_present(*p4d))
		return false;
	pud = pud_offset(p4d, pvmw->address);
	if (!pud_present(*pud))
		return false;
	pvmw->pmd = pmd_offset(pud, pvmw->address);
	/*
	 * Make sure the pmd value isn't cached in a register by the
	 * compiler and used as a stale value after we've observed a
	 * subsequent update.
	 */
	pmde = READ_ONCE(*pvmw->pmd);
	if (pmd_trans_huge(pmde) || is_pmd_migration_entry(pmde)) {
		pvmw->ptl = pmd_lock(mm, pvmw->pmd);
		if (likely(pmd_trans_huge(*pvmw->pmd))) {
			if (pvmw->flags & PVMW_MIGRATION)
				return not_found(pvmw);
			if (pmd_page(*pvmw->pmd) != page)
				return not_found(pvmw);
			return true;
		} else if (!pmd_present(*pvmw->pmd)) {
			if (thp_migration_supported()) {
				if (!(pvmw->flags & PVMW_MIGRATION))
					return not_found(pvmw);
				if (is_migration_entry(pmd_to_swp_entry(*pvmw->pmd))) {
					swp_entry_t entry = pmd_to_swp_entry(*pvmw->pmd);

					if (migration_entry_to_page(entry) != page)
						return not_found(pvmw);
					return true;
				}
			}
			return not_found(pvmw);
		} else {
			/* THP pmd was split under us: handle on pte level */
			spin_unlock(pvmw->ptl);
			pvmw->ptl = NULL;
		}
	} else if (!pmd_present(pmde)) {
		return false;
	}
	if (!map_pte(pvmw))
		goto next_pte;
	while (1) {
		if (check_pte(pvmw))
			return true;
next_pte:
		/* Seek to next pte only makes sense for THP */
		if (!PageTransHuge(pvmw->page) || PageHuge(pvmw->page))
			return not_found(pvmw);
		do {
			pvmw->address += PAGE_SIZE;
			if (pvmw->address >= pvmw->vma->vm_end ||
			    pvmw->address >=
					__vma_address(pvmw->page, pvmw->vma) +
					hpage_nr_pages(pvmw->page) * PAGE_SIZE)
				return not_found(pvmw);
			/* Did we cross page table boundary? */
			if (pvmw->address % PMD_SIZE == 0) {
				pte_unmap(pvmw->pte);
				if (pvmw->ptl) {
					spin_unlock(pvmw->ptl);
					pvmw->ptl = NULL;
				}
				goto restart;
			} else {
				pvmw->pte++;
			}
		} while (pte_none(*pvmw->pte));

		if (!pvmw->ptl) {
			pvmw->ptl = pte_lockptr(mm, pvmw->pmd);
			spin_lock(pvmw->ptl);
		}
	}
}