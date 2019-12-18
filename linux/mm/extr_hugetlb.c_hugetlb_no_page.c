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
struct vm_fault {unsigned long address; unsigned int flags; struct vm_area_struct* vma; } ;
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct hstate {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  unsigned long pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EEXIST ; 
 unsigned int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  HPAGE_RESV_UNMAPPED ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  PageHWPoison (struct page*) ; 
 int VM_FAULT_HWPOISON ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SET_HINDEX (int /*<<< orphan*/ ) ; 
 int VM_FAULT_SIGBUS ; 
 int VM_MAYSHARE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  VM_UFFD_MISSING ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_huge_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anon_vma_prepare (struct vm_area_struct*) ; 
 int /*<<< orphan*/  clear_huge_page (struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct page* find_lock_page (struct address_space*,unsigned long) ; 
 int handle_userfault (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hstate_index (struct hstate*) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 int huge_add_to_page_cache (struct page*,struct address_space*,unsigned long) ; 
 unsigned long huge_page_mask (struct hstate*) ; 
 unsigned long huge_page_shift (struct hstate*) ; 
 int /*<<< orphan*/ * huge_pte_lock (struct hstate*,struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hugepage_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  hugetlb_count_add (int /*<<< orphan*/ ,struct mm_struct*) ; 
 int hugetlb_cow (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ *) ; 
 size_t hugetlb_fault_mutex_hash (struct hstate*,struct address_space*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * hugetlb_fault_mutex_table ; 
 unsigned long i_size_read (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  make_huge_pte (struct vm_area_struct*,struct page*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*,int) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  restore_reserve_on_error (struct hstate*,struct vm_area_struct*,unsigned long,struct page*) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_huge_active (struct page*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ userfaultfd_missing (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_end_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 scalar_t__ vma_needs_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 int vmf_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t hugetlb_no_page(struct mm_struct *mm,
			struct vm_area_struct *vma,
			struct address_space *mapping, pgoff_t idx,
			unsigned long address, pte_t *ptep, unsigned int flags)
{
	struct hstate *h = hstate_vma(vma);
	vm_fault_t ret = VM_FAULT_SIGBUS;
	int anon_rmap = 0;
	unsigned long size;
	struct page *page;
	pte_t new_pte;
	spinlock_t *ptl;
	unsigned long haddr = address & huge_page_mask(h);
	bool new_page = false;

	/*
	 * Currently, we are forced to kill the process in the event the
	 * original mapper has unmapped pages from the child due to a failed
	 * COW. Warn that such a situation has occurred as it may not be obvious
	 */
	if (is_vma_resv_set(vma, HPAGE_RESV_UNMAPPED)) {
		pr_warn_ratelimited("PID %d killed due to inadequate hugepage pool\n",
			   current->pid);
		return ret;
	}

	/*
	 * Use page lock to guard against racing truncation
	 * before we get page_table_lock.
	 */
retry:
	page = find_lock_page(mapping, idx);
	if (!page) {
		size = i_size_read(mapping->host) >> huge_page_shift(h);
		if (idx >= size)
			goto out;

		/*
		 * Check for page in userfault range
		 */
		if (userfaultfd_missing(vma)) {
			u32 hash;
			struct vm_fault vmf = {
				.vma = vma,
				.address = haddr,
				.flags = flags,
				/*
				 * Hard to debug if it ends up being
				 * used by a callee that assumes
				 * something about the other
				 * uninitialized fields... same as in
				 * memory.c
				 */
			};

			/*
			 * hugetlb_fault_mutex must be dropped before
			 * handling userfault.  Reacquire after handling
			 * fault to make calling code simpler.
			 */
			hash = hugetlb_fault_mutex_hash(h, mapping, idx, haddr);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			ret = handle_userfault(&vmf, VM_UFFD_MISSING);
			mutex_lock(&hugetlb_fault_mutex_table[hash]);
			goto out;
		}

		page = alloc_huge_page(vma, haddr, 0);
		if (IS_ERR(page)) {
			/*
			 * Returning error will result in faulting task being
			 * sent SIGBUS.  The hugetlb fault mutex prevents two
			 * tasks from racing to fault in the same page which
			 * could result in false unable to allocate errors.
			 * Page migration does not take the fault mutex, but
			 * does a clear then write of pte's under page table
			 * lock.  Page fault code could race with migration,
			 * notice the clear pte and try to allocate a page
			 * here.  Before returning error, get ptl and make
			 * sure there really is no pte entry.
			 */
			ptl = huge_pte_lock(h, mm, ptep);
			if (!huge_pte_none(huge_ptep_get(ptep))) {
				ret = 0;
				spin_unlock(ptl);
				goto out;
			}
			spin_unlock(ptl);
			ret = vmf_error(PTR_ERR(page));
			goto out;
		}
		clear_huge_page(page, address, pages_per_huge_page(h));
		__SetPageUptodate(page);
		new_page = true;

		if (vma->vm_flags & VM_MAYSHARE) {
			int err = huge_add_to_page_cache(page, mapping, idx);
			if (err) {
				put_page(page);
				if (err == -EEXIST)
					goto retry;
				goto out;
			}
		} else {
			lock_page(page);
			if (unlikely(anon_vma_prepare(vma))) {
				ret = VM_FAULT_OOM;
				goto backout_unlocked;
			}
			anon_rmap = 1;
		}
	} else {
		/*
		 * If memory error occurs between mmap() and fault, some process
		 * don't have hwpoisoned swap entry for errored virtual address.
		 * So we need to block hugepage fault by PG_hwpoison bit check.
		 */
		if (unlikely(PageHWPoison(page))) {
			ret = VM_FAULT_HWPOISON |
				VM_FAULT_SET_HINDEX(hstate_index(h));
			goto backout_unlocked;
		}
	}

	/*
	 * If we are going to COW a private mapping later, we examine the
	 * pending reservations for this page now. This will ensure that
	 * any allocations necessary to record that reservation occur outside
	 * the spinlock.
	 */
	if ((flags & FAULT_FLAG_WRITE) && !(vma->vm_flags & VM_SHARED)) {
		if (vma_needs_reservation(h, vma, haddr) < 0) {
			ret = VM_FAULT_OOM;
			goto backout_unlocked;
		}
		/* Just decrements count, does not deallocate */
		vma_end_reservation(h, vma, haddr);
	}

	ptl = huge_pte_lock(h, mm, ptep);
	size = i_size_read(mapping->host) >> huge_page_shift(h);
	if (idx >= size)
		goto backout;

	ret = 0;
	if (!huge_pte_none(huge_ptep_get(ptep)))
		goto backout;

	if (anon_rmap) {
		ClearPagePrivate(page);
		hugepage_add_new_anon_rmap(page, vma, haddr);
	} else
		page_dup_rmap(page, true);
	new_pte = make_huge_pte(vma, page, ((vma->vm_flags & VM_WRITE)
				&& (vma->vm_flags & VM_SHARED)));
	set_huge_pte_at(mm, haddr, ptep, new_pte);

	hugetlb_count_add(pages_per_huge_page(h), mm);
	if ((flags & FAULT_FLAG_WRITE) && !(vma->vm_flags & VM_SHARED)) {
		/* Optimization, do the COW without a second fault */
		ret = hugetlb_cow(mm, vma, address, ptep, page, ptl);
	}

	spin_unlock(ptl);

	/*
	 * Only make newly allocated pages active.  Existing pages found
	 * in the pagecache could be !page_huge_active() if they have been
	 * isolated for migration.
	 */
	if (new_page)
		set_page_huge_active(page);

	unlock_page(page);
out:
	return ret;

backout:
	spin_unlock(ptl);
backout_unlocked:
	unlock_page(page);
	restore_reserve_on_error(h, vma, haddr, page);
	put_page(page);
	goto out;
}