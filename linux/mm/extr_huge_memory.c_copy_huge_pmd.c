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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/ * pgtable_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  add_mm_counter (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int is_swap_pmd (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_migration_entry_read (int /*<<< orphan*/ *) ; 
 struct page* mm_get_huge_zero_page (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_inc_nr_ptes (struct mm_struct*) ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*,int) ; 
 int /*<<< orphan*/  pgtable_trans_huge_deposit (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkold (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_swp_mksoft_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_swp_soft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_set_wrprotect (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_alloc_one (struct mm_struct*) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_huge_zero_page (int /*<<< orphan*/ *,struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swp_entry_to_pmd (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vma_is_anonymous (struct vm_area_struct*) ; 

int copy_huge_pmd(struct mm_struct *dst_mm, struct mm_struct *src_mm,
		  pmd_t *dst_pmd, pmd_t *src_pmd, unsigned long addr,
		  struct vm_area_struct *vma)
{
	spinlock_t *dst_ptl, *src_ptl;
	struct page *src_page;
	pmd_t pmd;
	pgtable_t pgtable = NULL;
	int ret = -ENOMEM;

	/* Skip if can be re-fill on fault */
	if (!vma_is_anonymous(vma))
		return 0;

	pgtable = pte_alloc_one(dst_mm);
	if (unlikely(!pgtable))
		goto out;

	dst_ptl = pmd_lock(dst_mm, dst_pmd);
	src_ptl = pmd_lockptr(src_mm, src_pmd);
	spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);

	ret = -EAGAIN;
	pmd = *src_pmd;

#ifdef CONFIG_ARCH_ENABLE_THP_MIGRATION
	if (unlikely(is_swap_pmd(pmd))) {
		swp_entry_t entry = pmd_to_swp_entry(pmd);

		VM_BUG_ON(!is_pmd_migration_entry(pmd));
		if (is_write_migration_entry(entry)) {
			make_migration_entry_read(&entry);
			pmd = swp_entry_to_pmd(entry);
			if (pmd_swp_soft_dirty(*src_pmd))
				pmd = pmd_swp_mksoft_dirty(pmd);
			set_pmd_at(src_mm, addr, src_pmd, pmd);
		}
		add_mm_counter(dst_mm, MM_ANONPAGES, HPAGE_PMD_NR);
		mm_inc_nr_ptes(dst_mm);
		pgtable_trans_huge_deposit(dst_mm, dst_pmd, pgtable);
		set_pmd_at(dst_mm, addr, dst_pmd, pmd);
		ret = 0;
		goto out_unlock;
	}
#endif

	if (unlikely(!pmd_trans_huge(pmd))) {
		pte_free(dst_mm, pgtable);
		goto out_unlock;
	}
	/*
	 * When page table lock is held, the huge zero pmd should not be
	 * under splitting since we don't split the page itself, only pmd to
	 * a page table.
	 */
	if (is_huge_zero_pmd(pmd)) {
		struct page *zero_page;
		/*
		 * get_huge_zero_page() will never allocate a new page here,
		 * since we already have a zero page to copy. It just takes a
		 * reference.
		 */
		zero_page = mm_get_huge_zero_page(dst_mm);
		set_huge_zero_page(pgtable, dst_mm, vma, addr, dst_pmd,
				zero_page);
		ret = 0;
		goto out_unlock;
	}

	src_page = pmd_page(pmd);
	VM_BUG_ON_PAGE(!PageHead(src_page), src_page);
	get_page(src_page);
	page_dup_rmap(src_page, true);
	add_mm_counter(dst_mm, MM_ANONPAGES, HPAGE_PMD_NR);
	mm_inc_nr_ptes(dst_mm);
	pgtable_trans_huge_deposit(dst_mm, dst_pmd, pgtable);

	pmdp_set_wrprotect(src_mm, addr, src_pmd);
	pmd = pmd_mkold(pmd_wrprotect(pmd));
	set_pmd_at(dst_mm, addr, dst_pmd, pmd);

	ret = 0;
out_unlock:
	spin_unlock(src_ptl);
	spin_unlock(dst_ptl);
out:
	return ret;
}