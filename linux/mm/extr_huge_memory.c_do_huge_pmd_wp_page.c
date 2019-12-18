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
typedef  int vm_fault_t ;
struct vm_fault {unsigned long address; int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pmd; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  anon_vma; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  HPAGE_PMD_ORDER ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  THP_FAULT_ALLOC ; 
 int /*<<< orphan*/  THP_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int VM_FAULT_FALLBACK ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_WRITE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 scalar_t__ __transparent_hugepage_enabled (struct vm_area_struct*) ; 
 int /*<<< orphan*/  add_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_hugepage_direct_gfpmask (struct vm_area_struct*) ; 
 struct page* alloc_hugepage_vma (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_huge_page (struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_user_huge_page (struct page*,struct page*,unsigned long,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_memcg_events (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int do_huge_pmd_wp_page_fallback (struct vm_fault*,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  maybe_pmd_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 int mem_cgroup_try_charge_delay (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  mk_huge_pmd (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_only_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,int) ; 
 int /*<<< orphan*/  pmd_lockptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_huge_clear_flush_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ pmdp_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prep_transhuge_page (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ reuse_swap_page (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transparent_hugepage_debug_cow () ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_mmu_cache_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

vm_fault_t do_huge_pmd_wp_page(struct vm_fault *vmf, pmd_t orig_pmd)
{
	struct vm_area_struct *vma = vmf->vma;
	struct page *page = NULL, *new_page;
	struct mem_cgroup *memcg;
	unsigned long haddr = vmf->address & HPAGE_PMD_MASK;
	struct mmu_notifier_range range;
	gfp_t huge_gfp;			/* for allocation and charge */
	vm_fault_t ret = 0;

	vmf->ptl = pmd_lockptr(vma->vm_mm, vmf->pmd);
	VM_BUG_ON_VMA(!vma->anon_vma, vma);
	if (is_huge_zero_pmd(orig_pmd))
		goto alloc;
	spin_lock(vmf->ptl);
	if (unlikely(!pmd_same(*vmf->pmd, orig_pmd)))
		goto out_unlock;

	page = pmd_page(orig_pmd);
	VM_BUG_ON_PAGE(!PageCompound(page) || !PageHead(page), page);
	/*
	 * We can only reuse the page if nobody else maps the huge page or it's
	 * part.
	 */
	if (!trylock_page(page)) {
		get_page(page);
		spin_unlock(vmf->ptl);
		lock_page(page);
		spin_lock(vmf->ptl);
		if (unlikely(!pmd_same(*vmf->pmd, orig_pmd))) {
			unlock_page(page);
			put_page(page);
			goto out_unlock;
		}
		put_page(page);
	}
	if (reuse_swap_page(page, NULL)) {
		pmd_t entry;
		entry = pmd_mkyoung(orig_pmd);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		if (pmdp_set_access_flags(vma, haddr, vmf->pmd, entry,  1))
			update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
		ret |= VM_FAULT_WRITE;
		unlock_page(page);
		goto out_unlock;
	}
	unlock_page(page);
	get_page(page);
	spin_unlock(vmf->ptl);
alloc:
	if (__transparent_hugepage_enabled(vma) &&
	    !transparent_hugepage_debug_cow()) {
		huge_gfp = alloc_hugepage_direct_gfpmask(vma);
		new_page = alloc_hugepage_vma(huge_gfp, vma, haddr, HPAGE_PMD_ORDER);
	} else
		new_page = NULL;

	if (likely(new_page)) {
		prep_transhuge_page(new_page);
	} else {
		if (!page) {
			split_huge_pmd(vma, vmf->pmd, vmf->address);
			ret |= VM_FAULT_FALLBACK;
		} else {
			ret = do_huge_pmd_wp_page_fallback(vmf, orig_pmd, page);
			if (ret & VM_FAULT_OOM) {
				split_huge_pmd(vma, vmf->pmd, vmf->address);
				ret |= VM_FAULT_FALLBACK;
			}
			put_page(page);
		}
		count_vm_event(THP_FAULT_FALLBACK);
		goto out;
	}

	if (unlikely(mem_cgroup_try_charge_delay(new_page, vma->vm_mm,
					huge_gfp, &memcg, true))) {
		put_page(new_page);
		split_huge_pmd(vma, vmf->pmd, vmf->address);
		if (page)
			put_page(page);
		ret |= VM_FAULT_FALLBACK;
		count_vm_event(THP_FAULT_FALLBACK);
		goto out;
	}

	count_vm_event(THP_FAULT_ALLOC);
	count_memcg_events(memcg, THP_FAULT_ALLOC, 1);

	if (!page)
		clear_huge_page(new_page, vmf->address, HPAGE_PMD_NR);
	else
		copy_user_huge_page(new_page, page, vmf->address,
				    vma, HPAGE_PMD_NR);
	__SetPageUptodate(new_page);

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				haddr, haddr + HPAGE_PMD_SIZE);
	mmu_notifier_invalidate_range_start(&range);

	spin_lock(vmf->ptl);
	if (page)
		put_page(page);
	if (unlikely(!pmd_same(*vmf->pmd, orig_pmd))) {
		spin_unlock(vmf->ptl);
		mem_cgroup_cancel_charge(new_page, memcg, true);
		put_page(new_page);
		goto out_mn;
	} else {
		pmd_t entry;
		entry = mk_huge_pmd(new_page, vma->vm_page_prot);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		pmdp_huge_clear_flush_notify(vma, haddr, vmf->pmd);
		page_add_new_anon_rmap(new_page, vma, haddr, true);
		mem_cgroup_commit_charge(new_page, memcg, false, true);
		lru_cache_add_active_or_unevictable(new_page, vma);
		set_pmd_at(vma->vm_mm, haddr, vmf->pmd, entry);
		update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
		if (!page) {
			add_mm_counter(vma->vm_mm, MM_ANONPAGES, HPAGE_PMD_NR);
		} else {
			VM_BUG_ON_PAGE(!PageHead(page), page);
			page_remove_rmap(page, true);
			put_page(page);
		}
		ret |= VM_FAULT_WRITE;
	}
	spin_unlock(vmf->ptl);
out_mn:
	/*
	 * No need to double call mmu_notifier->invalidate_range() callback as
	 * the above pmdp_huge_clear_flush_notify() did already call it.
	 */
	mmu_notifier_invalidate_range_only_end(&range);
out:
	return ret;
out_unlock:
	spin_unlock(vmf->ptl);
	return ret;
}