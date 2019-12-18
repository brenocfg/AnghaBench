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
typedef  int vm_fault_t ;
typedef  size_t u32 ;
struct vm_area_struct {int vm_flags; TYPE_1__* vm_file; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct hstate {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_2__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 unsigned int FAULT_FLAG_WRITE ; 
 int VM_FAULT_HWPOISON_LARGE ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SET_HINDEX (int /*<<< orphan*/ ) ; 
 int VM_MAYSHARE ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  hstate_index (struct hstate*) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 unsigned long huge_page_mask (struct hstate*) ; 
 int /*<<< orphan*/  huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/ * huge_pte_alloc (struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_lock (struct hstate*,struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_pte_mkdirty (int /*<<< orphan*/ ) ; 
 scalar_t__ huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 scalar_t__ huge_ptep_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int hugetlb_cow (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ *) ; 
 size_t hugetlb_fault_mutex_hash (struct hstate*,struct address_space*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * hugetlb_fault_mutex_table ; 
 int hugetlb_no_page (struct mm_struct*,struct vm_area_struct*,struct address_space*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* hugetlbfs_pagecache_page (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 int is_hugetlb_entry_hwpoisoned (int /*<<< orphan*/ ) ; 
 int is_hugetlb_entry_migration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migration_entry_wait_huge (struct vm_area_struct*,struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vma_end_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  vma_hugecache_offset (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 scalar_t__ vma_needs_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

vm_fault_t hugetlb_fault(struct mm_struct *mm, struct vm_area_struct *vma,
			unsigned long address, unsigned int flags)
{
	pte_t *ptep, entry;
	spinlock_t *ptl;
	vm_fault_t ret;
	u32 hash;
	pgoff_t idx;
	struct page *page = NULL;
	struct page *pagecache_page = NULL;
	struct hstate *h = hstate_vma(vma);
	struct address_space *mapping;
	int need_wait_lock = 0;
	unsigned long haddr = address & huge_page_mask(h);

	ptep = huge_pte_offset(mm, haddr, huge_page_size(h));
	if (ptep) {
		entry = huge_ptep_get(ptep);
		if (unlikely(is_hugetlb_entry_migration(entry))) {
			migration_entry_wait_huge(vma, mm, ptep);
			return 0;
		} else if (unlikely(is_hugetlb_entry_hwpoisoned(entry)))
			return VM_FAULT_HWPOISON_LARGE |
				VM_FAULT_SET_HINDEX(hstate_index(h));
	} else {
		ptep = huge_pte_alloc(mm, haddr, huge_page_size(h));
		if (!ptep)
			return VM_FAULT_OOM;
	}

	mapping = vma->vm_file->f_mapping;
	idx = vma_hugecache_offset(h, vma, haddr);

	/*
	 * Serialize hugepage allocation and instantiation, so that we don't
	 * get spurious allocation failures if two CPUs race to instantiate
	 * the same page in the page cache.
	 */
	hash = hugetlb_fault_mutex_hash(h, mapping, idx, haddr);
	mutex_lock(&hugetlb_fault_mutex_table[hash]);

	entry = huge_ptep_get(ptep);
	if (huge_pte_none(entry)) {
		ret = hugetlb_no_page(mm, vma, mapping, idx, address, ptep, flags);
		goto out_mutex;
	}

	ret = 0;

	/*
	 * entry could be a migration/hwpoison entry at this point, so this
	 * check prevents the kernel from going below assuming that we have
	 * a active hugepage in pagecache. This goto expects the 2nd page fault,
	 * and is_hugetlb_entry_(migration|hwpoisoned) check will properly
	 * handle it.
	 */
	if (!pte_present(entry))
		goto out_mutex;

	/*
	 * If we are going to COW the mapping later, we examine the pending
	 * reservations for this page now. This will ensure that any
	 * allocations necessary to record that reservation occur outside the
	 * spinlock. For private mappings, we also lookup the pagecache
	 * page now as it is used to determine if a reservation has been
	 * consumed.
	 */
	if ((flags & FAULT_FLAG_WRITE) && !huge_pte_write(entry)) {
		if (vma_needs_reservation(h, vma, haddr) < 0) {
			ret = VM_FAULT_OOM;
			goto out_mutex;
		}
		/* Just decrements count, does not deallocate */
		vma_end_reservation(h, vma, haddr);

		if (!(vma->vm_flags & VM_MAYSHARE))
			pagecache_page = hugetlbfs_pagecache_page(h,
								vma, haddr);
	}

	ptl = huge_pte_lock(h, mm, ptep);

	/* Check for a racing update before calling hugetlb_cow */
	if (unlikely(!pte_same(entry, huge_ptep_get(ptep))))
		goto out_ptl;

	/*
	 * hugetlb_cow() requires page locks of pte_page(entry) and
	 * pagecache_page, so here we need take the former one
	 * when page != pagecache_page or !pagecache_page.
	 */
	page = pte_page(entry);
	if (page != pagecache_page)
		if (!trylock_page(page)) {
			need_wait_lock = 1;
			goto out_ptl;
		}

	get_page(page);

	if (flags & FAULT_FLAG_WRITE) {
		if (!huge_pte_write(entry)) {
			ret = hugetlb_cow(mm, vma, address, ptep,
					  pagecache_page, ptl);
			goto out_put_page;
		}
		entry = huge_pte_mkdirty(entry);
	}
	entry = pte_mkyoung(entry);
	if (huge_ptep_set_access_flags(vma, haddr, ptep, entry,
						flags & FAULT_FLAG_WRITE))
		update_mmu_cache(vma, haddr, ptep);
out_put_page:
	if (page != pagecache_page)
		unlock_page(page);
	put_page(page);
out_ptl:
	spin_unlock(ptl);

	if (pagecache_page) {
		unlock_page(pagecache_page);
		put_page(pagecache_page);
	}
out_mutex:
	mutex_unlock(&hugetlb_fault_mutex_table[hash]);
	/*
	 * Generally it's safe to hold refcount during waiting page lock. But
	 * here we just wait to defer the next page fault to avoid busy loop and
	 * the page is not used after unlocked before returning from the current
	 * page fault. So we are safe from accessing freed page, even if we wait
	 * here without taking refcount.
	 */
	if (need_wait_lock)
		wait_on_page_locked(page);
	return ret;
}