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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct mm_struct {int dummy; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  PTR_ERR (struct page*) ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_huge_page (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  anon_vma_prepare (struct vm_area_struct*) ; 
 int /*<<< orphan*/  copy_user_huge_page (struct page*,struct page*,unsigned long,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 unsigned long huge_page_mask (struct hstate*) ; 
 scalar_t__ huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/  huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  huge_ptep_clear_flush (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hugepage_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  make_huge_pte (struct vm_area_struct*,struct page*,int) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,struct mm_struct*,unsigned long,scalar_t__) ; 
 int page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_move_anon_rmap (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,int) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  restore_reserve_on_error (struct hstate*,struct vm_area_struct*,unsigned long,struct page*) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_ptep_writable (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_huge_active (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_ref_private (struct mm_struct*,struct vm_area_struct*,struct page*,unsigned long) ; 
 int /*<<< orphan*/  vmf_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t hugetlb_cow(struct mm_struct *mm, struct vm_area_struct *vma,
		       unsigned long address, pte_t *ptep,
		       struct page *pagecache_page, spinlock_t *ptl)
{
	pte_t pte;
	struct hstate *h = hstate_vma(vma);
	struct page *old_page, *new_page;
	int outside_reserve = 0;
	vm_fault_t ret = 0;
	unsigned long haddr = address & huge_page_mask(h);
	struct mmu_notifier_range range;

	pte = huge_ptep_get(ptep);
	old_page = pte_page(pte);

retry_avoidcopy:
	/* If no-one else is actually using this page, avoid the copy
	 * and just make the page writable */
	if (page_mapcount(old_page) == 1 && PageAnon(old_page)) {
		page_move_anon_rmap(old_page, vma);
		set_huge_ptep_writable(vma, haddr, ptep);
		return 0;
	}

	/*
	 * If the process that created a MAP_PRIVATE mapping is about to
	 * perform a COW due to a shared page count, attempt to satisfy
	 * the allocation without using the existing reserves. The pagecache
	 * page is used to determine if the reserve at this address was
	 * consumed or not. If reserves were used, a partial faulted mapping
	 * at the time of fork() could consume its reserves on COW instead
	 * of the full address range.
	 */
	if (is_vma_resv_set(vma, HPAGE_RESV_OWNER) &&
			old_page != pagecache_page)
		outside_reserve = 1;

	get_page(old_page);

	/*
	 * Drop page table lock as buddy allocator may be called. It will
	 * be acquired again before returning to the caller, as expected.
	 */
	spin_unlock(ptl);
	new_page = alloc_huge_page(vma, haddr, outside_reserve);

	if (IS_ERR(new_page)) {
		/*
		 * If a process owning a MAP_PRIVATE mapping fails to COW,
		 * it is due to references held by a child and an insufficient
		 * huge page pool. To guarantee the original mappers
		 * reliability, unmap the page from child processes. The child
		 * may get SIGKILLed if it later faults.
		 */
		if (outside_reserve) {
			put_page(old_page);
			BUG_ON(huge_pte_none(pte));
			unmap_ref_private(mm, vma, old_page, haddr);
			BUG_ON(huge_pte_none(pte));
			spin_lock(ptl);
			ptep = huge_pte_offset(mm, haddr, huge_page_size(h));
			if (likely(ptep &&
				   pte_same(huge_ptep_get(ptep), pte)))
				goto retry_avoidcopy;
			/*
			 * race occurs while re-acquiring page table
			 * lock, and our job is done.
			 */
			return 0;
		}

		ret = vmf_error(PTR_ERR(new_page));
		goto out_release_old;
	}

	/*
	 * When the original hugepage is shared one, it does not have
	 * anon_vma prepared.
	 */
	if (unlikely(anon_vma_prepare(vma))) {
		ret = VM_FAULT_OOM;
		goto out_release_all;
	}

	copy_user_huge_page(new_page, old_page, address, vma,
			    pages_per_huge_page(h));
	__SetPageUptodate(new_page);

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm, haddr,
				haddr + huge_page_size(h));
	mmu_notifier_invalidate_range_start(&range);

	/*
	 * Retake the page table lock to check for racing updates
	 * before the page tables are altered
	 */
	spin_lock(ptl);
	ptep = huge_pte_offset(mm, haddr, huge_page_size(h));
	if (likely(ptep && pte_same(huge_ptep_get(ptep), pte))) {
		ClearPagePrivate(new_page);

		/* Break COW */
		huge_ptep_clear_flush(vma, haddr, ptep);
		mmu_notifier_invalidate_range(mm, range.start, range.end);
		set_huge_pte_at(mm, haddr, ptep,
				make_huge_pte(vma, new_page, 1));
		page_remove_rmap(old_page, true);
		hugepage_add_new_anon_rmap(new_page, vma, haddr);
		set_page_huge_active(new_page);
		/* Make the old page be freed below */
		new_page = old_page;
	}
	spin_unlock(ptl);
	mmu_notifier_invalidate_range_end(&range);
out_release_all:
	restore_reserve_on_error(h, vma, haddr, new_page);
	put_page(new_page);
out_release_old:
	put_page(old_page);

	spin_lock(ptl); /* Caller expects lock to be held */
	return ret;
}