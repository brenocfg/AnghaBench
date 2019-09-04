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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int EBUSY ; 
 struct page* ERR_PTR (int) ; 
 unsigned int FOLL_MIGRATION ; 
 unsigned int FOLL_NUMA ; 
 unsigned int FOLL_SPLIT ; 
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PMD_SHIFT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_HUGETLB ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 struct page* follow_devmap_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_huge_pd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* follow_huge_pmd (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_page_pte (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_trans_huge_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_huge_zero_page (struct page*) ; 
 scalar_t__ is_hugepd (int /*<<< orphan*/ ) ; 
 scalar_t__ is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct page* no_page_table (struct vm_area_struct*,unsigned int) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_protnone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int split_huge_page (struct page*) ; 
 int /*<<< orphan*/  split_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ thp_migration_supported () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static struct page *follow_pmd_mask(struct vm_area_struct *vma,
				    unsigned long address, pud_t *pudp,
				    unsigned int flags, unsigned int *page_mask)
{
	pmd_t *pmd, pmdval;
	spinlock_t *ptl;
	struct page *page;
	struct mm_struct *mm = vma->vm_mm;

	pmd = pmd_offset(pudp, address);
	/*
	 * The READ_ONCE() will stabilize the pmdval in a register or
	 * on the stack so that it will stop changing under the code.
	 */
	pmdval = READ_ONCE(*pmd);
	if (pmd_none(pmdval))
		return no_page_table(vma, flags);
	if (pmd_huge(pmdval) && vma->vm_flags & VM_HUGETLB) {
		page = follow_huge_pmd(mm, address, pmd, flags);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}
	if (is_hugepd(__hugepd(pmd_val(pmdval)))) {
		page = follow_huge_pd(vma, address,
				      __hugepd(pmd_val(pmdval)), flags,
				      PMD_SHIFT);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}
retry:
	if (!pmd_present(pmdval)) {
		if (likely(!(flags & FOLL_MIGRATION)))
			return no_page_table(vma, flags);
		VM_BUG_ON(thp_migration_supported() &&
				  !is_pmd_migration_entry(pmdval));
		if (is_pmd_migration_entry(pmdval))
			pmd_migration_entry_wait(mm, pmd);
		pmdval = READ_ONCE(*pmd);
		/*
		 * MADV_DONTNEED may convert the pmd to null because
		 * mmap_sem is held in read mode
		 */
		if (pmd_none(pmdval))
			return no_page_table(vma, flags);
		goto retry;
	}
	if (pmd_devmap(pmdval)) {
		ptl = pmd_lock(mm, pmd);
		page = follow_devmap_pmd(vma, address, pmd, flags);
		spin_unlock(ptl);
		if (page)
			return page;
	}
	if (likely(!pmd_trans_huge(pmdval)))
		return follow_page_pte(vma, address, pmd, flags);

	if ((flags & FOLL_NUMA) && pmd_protnone(pmdval))
		return no_page_table(vma, flags);

retry_locked:
	ptl = pmd_lock(mm, pmd);
	if (unlikely(pmd_none(*pmd))) {
		spin_unlock(ptl);
		return no_page_table(vma, flags);
	}
	if (unlikely(!pmd_present(*pmd))) {
		spin_unlock(ptl);
		if (likely(!(flags & FOLL_MIGRATION)))
			return no_page_table(vma, flags);
		pmd_migration_entry_wait(mm, pmd);
		goto retry_locked;
	}
	if (unlikely(!pmd_trans_huge(*pmd))) {
		spin_unlock(ptl);
		return follow_page_pte(vma, address, pmd, flags);
	}
	if (flags & FOLL_SPLIT) {
		int ret;
		page = pmd_page(*pmd);
		if (is_huge_zero_page(page)) {
			spin_unlock(ptl);
			ret = 0;
			split_huge_pmd(vma, pmd, address);
			if (pmd_trans_unstable(pmd))
				ret = -EBUSY;
		} else {
			get_page(page);
			spin_unlock(ptl);
			lock_page(page);
			ret = split_huge_page(page);
			unlock_page(page);
			put_page(page);
			if (pmd_none(*pmd))
				return no_page_table(vma, flags);
		}

		return ret ? ERR_PTR(ret) :
			follow_page_pte(vma, address, pmd, flags);
	}
	page = follow_trans_huge_pmd(vma, address, pmd, flags);
	spin_unlock(ptl);
	*page_mask = HPAGE_PMD_NR - 1;
	return page;
}