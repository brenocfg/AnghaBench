#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int vm_fault_t ;
struct TYPE_19__ {scalar_t__ val; } ;
typedef  TYPE_3__ swp_entry_t ;
struct vm_fault {int flags; int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pte; int /*<<< orphan*/  address; int /*<<< orphan*/  orig_pte; int /*<<< orphan*/  pmd; TYPE_13__* page; struct vm_area_struct* vma; } ;
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; } ;
struct swap_info_struct {int flags; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_18__ {TYPE_1__* ops; } ;
struct TYPE_17__ {int (* migrate_to_ram ) (struct vm_fault*) ;} ;
struct TYPE_16__ {TYPE_2__* pgmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAYACCT_PF_SWAPIN ; 
 int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  MM_SWAPENTS ; 
 int /*<<< orphan*/  PGMAJFAULT ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 scalar_t__ PageMlocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int RMAP_EXCLUSIVE ; 
 int SWP_SYNCHRONOUS_IO ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_HWPOISON ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_RETRY ; 
 int VM_FAULT_SIGBUS ; 
 int VM_FAULT_WRITE ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  __SetPageLocked (struct page*) ; 
 int /*<<< orphan*/  __SetPageSwapBacked (struct page*) ; 
 int __swap_count (TYPE_3__) ; 
 int /*<<< orphan*/  activate_page (struct page*) ; 
 struct page* alloc_page_vma (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_do_swap_page (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_memcg_event_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_mm_counter_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayacct_clear_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayacct_set_flag (int /*<<< orphan*/ ) ; 
 TYPE_13__* device_private_entry_to_page (TYPE_3__) ; 
 int /*<<< orphan*/  do_page_add_anon_rmap (struct page*,struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 int do_wp_page (struct vm_fault*) ; 
 int /*<<< orphan*/  flush_icache_page (struct vm_area_struct*,struct page*) ; 
 int /*<<< orphan*/  inc_mm_counter_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_device_private_entry (TYPE_3__) ; 
 scalar_t__ is_hwpoison_entry (TYPE_3__) ; 
 scalar_t__ is_migration_entry (TYPE_3__) ; 
 struct page* ksm_might_need_to_copy (struct page*,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int lock_page_or_retry (struct page*,int /*<<< orphan*/ ,int) ; 
 struct page* lookup_swap_cache (TYPE_3__,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  lru_cache_add_anon (struct page*) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 scalar_t__ mem_cgroup_swap_full (struct page*) ; 
 scalar_t__ mem_cgroup_try_charge_delay (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  migration_entry_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int non_swap_entry (TYPE_3__) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  print_bad_pte (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mksoft_dirty (int /*<<< orphan*/ ) ; 
 void* pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_swp_soft_dirty (int /*<<< orphan*/ ) ; 
 TYPE_3__ pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ reuse_swap_page (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (struct page*,scalar_t__) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct vm_fault*) ; 
 int /*<<< orphan*/  swap_free (TYPE_3__) ; 
 int /*<<< orphan*/  swap_readpage (struct page*,int) ; 
 struct page* swapin_readahead (TYPE_3__,int /*<<< orphan*/ ,struct vm_fault*) ; 
 struct swap_info_struct* swp_swap_info (TYPE_3__) ; 
 int /*<<< orphan*/  try_to_free_swap (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

vm_fault_t do_swap_page(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct page *page = NULL, *swapcache;
	struct mem_cgroup *memcg;
	swp_entry_t entry;
	pte_t pte;
	int locked;
	int exclusive = 0;
	vm_fault_t ret = 0;

	if (!pte_unmap_same(vma->vm_mm, vmf->pmd, vmf->pte, vmf->orig_pte))
		goto out;

	entry = pte_to_swp_entry(vmf->orig_pte);
	if (unlikely(non_swap_entry(entry))) {
		if (is_migration_entry(entry)) {
			migration_entry_wait(vma->vm_mm, vmf->pmd,
					     vmf->address);
		} else if (is_device_private_entry(entry)) {
			vmf->page = device_private_entry_to_page(entry);
			ret = vmf->page->pgmap->ops->migrate_to_ram(vmf);
		} else if (is_hwpoison_entry(entry)) {
			ret = VM_FAULT_HWPOISON;
		} else {
			print_bad_pte(vma, vmf->address, vmf->orig_pte, NULL);
			ret = VM_FAULT_SIGBUS;
		}
		goto out;
	}


	delayacct_set_flag(DELAYACCT_PF_SWAPIN);
	page = lookup_swap_cache(entry, vma, vmf->address);
	swapcache = page;

	if (!page) {
		struct swap_info_struct *si = swp_swap_info(entry);

		if (si->flags & SWP_SYNCHRONOUS_IO &&
				__swap_count(entry) == 1) {
			/* skip swapcache */
			page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma,
							vmf->address);
			if (page) {
				__SetPageLocked(page);
				__SetPageSwapBacked(page);
				set_page_private(page, entry.val);
				lru_cache_add_anon(page);
				swap_readpage(page, true);
			}
		} else {
			page = swapin_readahead(entry, GFP_HIGHUSER_MOVABLE,
						vmf);
			swapcache = page;
		}

		if (!page) {
			/*
			 * Back out if somebody else faulted in this pte
			 * while we released the pte lock.
			 */
			vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd,
					vmf->address, &vmf->ptl);
			if (likely(pte_same(*vmf->pte, vmf->orig_pte)))
				ret = VM_FAULT_OOM;
			delayacct_clear_flag(DELAYACCT_PF_SWAPIN);
			goto unlock;
		}

		/* Had to read the page from swap area: Major fault */
		ret = VM_FAULT_MAJOR;
		count_vm_event(PGMAJFAULT);
		count_memcg_event_mm(vma->vm_mm, PGMAJFAULT);
	} else if (PageHWPoison(page)) {
		/*
		 * hwpoisoned dirty swapcache pages are kept for killing
		 * owner processes (which may be unknown at hwpoison time)
		 */
		ret = VM_FAULT_HWPOISON;
		delayacct_clear_flag(DELAYACCT_PF_SWAPIN);
		goto out_release;
	}

	locked = lock_page_or_retry(page, vma->vm_mm, vmf->flags);

	delayacct_clear_flag(DELAYACCT_PF_SWAPIN);
	if (!locked) {
		ret |= VM_FAULT_RETRY;
		goto out_release;
	}

	/*
	 * Make sure try_to_free_swap or reuse_swap_page or swapoff did not
	 * release the swapcache from under us.  The page pin, and pte_same
	 * test below, are not enough to exclude that.  Even if it is still
	 * swapcache, we need to check that the page's swap has not changed.
	 */
	if (unlikely((!PageSwapCache(page) ||
			page_private(page) != entry.val)) && swapcache)
		goto out_page;

	page = ksm_might_need_to_copy(page, vma, vmf->address);
	if (unlikely(!page)) {
		ret = VM_FAULT_OOM;
		page = swapcache;
		goto out_page;
	}

	if (mem_cgroup_try_charge_delay(page, vma->vm_mm, GFP_KERNEL,
					&memcg, false)) {
		ret = VM_FAULT_OOM;
		goto out_page;
	}

	/*
	 * Back out if somebody else already faulted in this pte.
	 */
	vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd, vmf->address,
			&vmf->ptl);
	if (unlikely(!pte_same(*vmf->pte, vmf->orig_pte)))
		goto out_nomap;

	if (unlikely(!PageUptodate(page))) {
		ret = VM_FAULT_SIGBUS;
		goto out_nomap;
	}

	/*
	 * The page isn't present yet, go ahead with the fault.
	 *
	 * Be careful about the sequence of operations here.
	 * To get its accounting right, reuse_swap_page() must be called
	 * while the page is counted on swap but not yet in mapcount i.e.
	 * before page_add_anon_rmap() and swap_free(); try_to_free_swap()
	 * must be called after the swap_free(), or it will never succeed.
	 */

	inc_mm_counter_fast(vma->vm_mm, MM_ANONPAGES);
	dec_mm_counter_fast(vma->vm_mm, MM_SWAPENTS);
	pte = mk_pte(page, vma->vm_page_prot);
	if ((vmf->flags & FAULT_FLAG_WRITE) && reuse_swap_page(page, NULL)) {
		pte = maybe_mkwrite(pte_mkdirty(pte), vma);
		vmf->flags &= ~FAULT_FLAG_WRITE;
		ret |= VM_FAULT_WRITE;
		exclusive = RMAP_EXCLUSIVE;
	}
	flush_icache_page(vma, page);
	if (pte_swp_soft_dirty(vmf->orig_pte))
		pte = pte_mksoft_dirty(pte);
	set_pte_at(vma->vm_mm, vmf->address, vmf->pte, pte);
	arch_do_swap_page(vma->vm_mm, vma, vmf->address, pte, vmf->orig_pte);
	vmf->orig_pte = pte;

	/* ksm created a completely new copy */
	if (unlikely(page != swapcache && swapcache)) {
		page_add_new_anon_rmap(page, vma, vmf->address, false);
		mem_cgroup_commit_charge(page, memcg, false, false);
		lru_cache_add_active_or_unevictable(page, vma);
	} else {
		do_page_add_anon_rmap(page, vma, vmf->address, exclusive);
		mem_cgroup_commit_charge(page, memcg, true, false);
		activate_page(page);
	}

	swap_free(entry);
	if (mem_cgroup_swap_full(page) ||
	    (vma->vm_flags & VM_LOCKED) || PageMlocked(page))
		try_to_free_swap(page);
	unlock_page(page);
	if (page != swapcache && swapcache) {
		/*
		 * Hold the lock to avoid the swap entry to be reused
		 * until we take the PT lock for the pte_same() check
		 * (to avoid false positives from pte_same). For
		 * further safety release the lock after the swap_free
		 * so that the swap count won't change under a
		 * parallel locked swapcache.
		 */
		unlock_page(swapcache);
		put_page(swapcache);
	}

	if (vmf->flags & FAULT_FLAG_WRITE) {
		ret |= do_wp_page(vmf);
		if (ret & VM_FAULT_ERROR)
			ret &= VM_FAULT_ERROR;
		goto out;
	}

	/* No need to invalidate - it was non-present before */
	update_mmu_cache(vma, vmf->address, vmf->pte);
unlock:
	pte_unmap_unlock(vmf->pte, vmf->ptl);
out:
	return ret;
out_nomap:
	mem_cgroup_cancel_charge(page, memcg, false);
	pte_unmap_unlock(vmf->pte, vmf->ptl);
out_page:
	unlock_page(page);
out_release:
	put_page(page);
	if (page != swapcache && swapcache) {
		unlock_page(swapcache);
		put_page(swapcache);
	}
	return ret;
}