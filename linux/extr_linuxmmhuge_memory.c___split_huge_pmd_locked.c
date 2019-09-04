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
struct vm_area_struct {unsigned long vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_page_prot; struct mm_struct* vm_mm; } ;
struct page {int /*<<< orphan*/  _mapcount; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HPAGE_PMD_MASK ; 
 int HPAGE_PMD_NR ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  NR_ANON_THPS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageReferenced (struct page*) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int /*<<< orphan*/  THP_SPLIT_PMD ; 
 scalar_t__ TestClearPageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  TestSetPageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int /*<<< orphan*/  __dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 void __split_huge_zero_page_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_mm_counter (struct mm_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ arch_needs_pgtable_deposit () ; 
 scalar_t__ atomic_add_negative (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int compound_mapcount (struct page*) ; 
 int /*<<< orphan*/  compound_mapcount_ptr (struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int is_write_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_migration_entry (struct page*,int) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_counter_file (struct page*) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,int) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgtable_trans_huge_withdraw (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_dirty (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pmd_soft_dirty (int /*<<< orphan*/ ) ; 
 int pmd_swp_soft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int pmd_write (int /*<<< orphan*/ ) ; 
 int pmd_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_huge_clear_flush_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmdp_invalidate (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mksoft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_swp_mksoft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vma_is_anonymous (struct vm_area_struct*) ; 
 scalar_t__ vma_is_dax (struct vm_area_struct*) ; 
 int /*<<< orphan*/  zap_deposited_table (struct mm_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __split_huge_pmd_locked(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long haddr, bool freeze)
{
	struct mm_struct *mm = vma->vm_mm;
	struct page *page;
	pgtable_t pgtable;
	pmd_t old_pmd, _pmd;
	bool young, write, soft_dirty, pmd_migration = false;
	unsigned long addr;
	int i;

	VM_BUG_ON(haddr & ~HPAGE_PMD_MASK);
	VM_BUG_ON_VMA(vma->vm_start > haddr, vma);
	VM_BUG_ON_VMA(vma->vm_end < haddr + HPAGE_PMD_SIZE, vma);
	VM_BUG_ON(!is_pmd_migration_entry(*pmd) && !pmd_trans_huge(*pmd)
				&& !pmd_devmap(*pmd));

	count_vm_event(THP_SPLIT_PMD);

	if (!vma_is_anonymous(vma)) {
		_pmd = pmdp_huge_clear_flush_notify(vma, haddr, pmd);
		/*
		 * We are going to unmap this huge page. So
		 * just go ahead and zap it
		 */
		if (arch_needs_pgtable_deposit())
			zap_deposited_table(mm, pmd);
		if (vma_is_dax(vma))
			return;
		page = pmd_page(_pmd);
		if (!PageDirty(page) && pmd_dirty(_pmd))
			set_page_dirty(page);
		if (!PageReferenced(page) && pmd_young(_pmd))
			SetPageReferenced(page);
		page_remove_rmap(page, true);
		put_page(page);
		add_mm_counter(mm, mm_counter_file(page), -HPAGE_PMD_NR);
		return;
	} else if (is_huge_zero_pmd(*pmd)) {
		/*
		 * FIXME: Do we want to invalidate secondary mmu by calling
		 * mmu_notifier_invalidate_range() see comments below inside
		 * __split_huge_pmd() ?
		 *
		 * We are going from a zero huge page write protected to zero
		 * small page also write protected so it does not seems useful
		 * to invalidate secondary mmu at this time.
		 */
		return __split_huge_zero_page_pmd(vma, haddr, pmd);
	}

	/*
	 * Up to this point the pmd is present and huge and userland has the
	 * whole access to the hugepage during the split (which happens in
	 * place). If we overwrite the pmd with the not-huge version pointing
	 * to the pte here (which of course we could if all CPUs were bug
	 * free), userland could trigger a small page size TLB miss on the
	 * small sized TLB while the hugepage TLB entry is still established in
	 * the huge TLB. Some CPU doesn't like that.
	 * See http://support.amd.com/us/Processor_TechDocs/41322.pdf, Erratum
	 * 383 on page 93. Intel should be safe but is also warns that it's
	 * only safe if the permission and cache attributes of the two entries
	 * loaded in the two TLB is identical (which should be the case here).
	 * But it is generally safer to never allow small and huge TLB entries
	 * for the same virtual address to be loaded simultaneously. So instead
	 * of doing "pmd_populate(); flush_pmd_tlb_range();" we first mark the
	 * current pmd notpresent (atomically because here the pmd_trans_huge
	 * must remain set at all times on the pmd until the split is complete
	 * for this pmd), then we flush the SMP TLB and finally we write the
	 * non-huge version of the pmd entry with pmd_populate.
	 */
	old_pmd = pmdp_invalidate(vma, haddr, pmd);

	pmd_migration = is_pmd_migration_entry(old_pmd);
	if (unlikely(pmd_migration)) {
		swp_entry_t entry;

		entry = pmd_to_swp_entry(old_pmd);
		page = pfn_to_page(swp_offset(entry));
		write = is_write_migration_entry(entry);
		young = false;
		soft_dirty = pmd_swp_soft_dirty(old_pmd);
	} else {
		page = pmd_page(old_pmd);
		if (pmd_dirty(old_pmd))
			SetPageDirty(page);
		write = pmd_write(old_pmd);
		young = pmd_young(old_pmd);
		soft_dirty = pmd_soft_dirty(old_pmd);
	}
	VM_BUG_ON_PAGE(!page_count(page), page);
	page_ref_add(page, HPAGE_PMD_NR - 1);

	/*
	 * Withdraw the table only after we mark the pmd entry invalid.
	 * This's critical for some architectures (Power).
	 */
	pgtable = pgtable_trans_huge_withdraw(mm, pmd);
	pmd_populate(mm, &_pmd, pgtable);

	for (i = 0, addr = haddr; i < HPAGE_PMD_NR; i++, addr += PAGE_SIZE) {
		pte_t entry, *pte;
		/*
		 * Note that NUMA hinting access restrictions are not
		 * transferred to avoid any possibility of altering
		 * permissions across VMAs.
		 */
		if (freeze || pmd_migration) {
			swp_entry_t swp_entry;
			swp_entry = make_migration_entry(page + i, write);
			entry = swp_entry_to_pte(swp_entry);
			if (soft_dirty)
				entry = pte_swp_mksoft_dirty(entry);
		} else {
			entry = mk_pte(page + i, READ_ONCE(vma->vm_page_prot));
			entry = maybe_mkwrite(entry, vma);
			if (!write)
				entry = pte_wrprotect(entry);
			if (!young)
				entry = pte_mkold(entry);
			if (soft_dirty)
				entry = pte_mksoft_dirty(entry);
		}
		pte = pte_offset_map(&_pmd, addr);
		BUG_ON(!pte_none(*pte));
		set_pte_at(mm, addr, pte, entry);
		atomic_inc(&page[i]._mapcount);
		pte_unmap(pte);
	}

	/*
	 * Set PG_double_map before dropping compound_mapcount to avoid
	 * false-negative page_mapped().
	 */
	if (compound_mapcount(page) > 1 && !TestSetPageDoubleMap(page)) {
		for (i = 0; i < HPAGE_PMD_NR; i++)
			atomic_inc(&page[i]._mapcount);
	}

	if (atomic_add_negative(-1, compound_mapcount_ptr(page))) {
		/* Last compound_mapcount is gone. */
		__dec_node_page_state(page, NR_ANON_THPS);
		if (TestClearPageDoubleMap(page)) {
			/* No need in mapcount reference anymore */
			for (i = 0; i < HPAGE_PMD_NR; i++)
				atomic_dec(&page[i]._mapcount);
		}
	}

	smp_wmb(); /* make pte visible before pmd */
	pmd_populate(mm, pmd, pgtable);

	if (freeze) {
		for (i = 0; i < HPAGE_PMD_NR; i++) {
			page_remove_rmap(page + i, false);
			put_page(page + i);
		}
	}
}