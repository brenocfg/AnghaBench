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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  scalar_t__ pgtable_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  THP_FAULT_ALLOC ; 
 int /*<<< orphan*/  THP_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int VM_FAULT_FALLBACK ; 
 int VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_UFFD_MISSING ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  add_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_stable_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_huge_page (struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_memcg_events (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int handle_userfault (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  maybe_pmd_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 scalar_t__ mem_cgroup_try_charge_delay (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  mk_huge_pmd (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_inc_nr_ptes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  pgtable_trans_huge_deposit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_alloc_one (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pmd_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ userfaultfd_missing (struct vm_area_struct*) ; 

__attribute__((used)) static vm_fault_t __do_huge_pmd_anonymous_page(struct vm_fault *vmf,
			struct page *page, gfp_t gfp)
{
	struct vm_area_struct *vma = vmf->vma;
	struct mem_cgroup *memcg;
	pgtable_t pgtable;
	unsigned long haddr = vmf->address & HPAGE_PMD_MASK;
	vm_fault_t ret = 0;

	VM_BUG_ON_PAGE(!PageCompound(page), page);

	if (mem_cgroup_try_charge_delay(page, vma->vm_mm, gfp, &memcg, true)) {
		put_page(page);
		count_vm_event(THP_FAULT_FALLBACK);
		return VM_FAULT_FALLBACK;
	}

	pgtable = pte_alloc_one(vma->vm_mm);
	if (unlikely(!pgtable)) {
		ret = VM_FAULT_OOM;
		goto release;
	}

	clear_huge_page(page, vmf->address, HPAGE_PMD_NR);
	/*
	 * The memory barrier inside __SetPageUptodate makes sure that
	 * clear_huge_page writes become visible before the set_pmd_at()
	 * write.
	 */
	__SetPageUptodate(page);

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	if (unlikely(!pmd_none(*vmf->pmd))) {
		goto unlock_release;
	} else {
		pmd_t entry;

		ret = check_stable_address_space(vma->vm_mm);
		if (ret)
			goto unlock_release;

		/* Deliver the page fault to userland */
		if (userfaultfd_missing(vma)) {
			vm_fault_t ret2;

			spin_unlock(vmf->ptl);
			mem_cgroup_cancel_charge(page, memcg, true);
			put_page(page);
			pte_free(vma->vm_mm, pgtable);
			ret2 = handle_userfault(vmf, VM_UFFD_MISSING);
			VM_BUG_ON(ret2 & VM_FAULT_FALLBACK);
			return ret2;
		}

		entry = mk_huge_pmd(page, vma->vm_page_prot);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		page_add_new_anon_rmap(page, vma, haddr, true);
		mem_cgroup_commit_charge(page, memcg, false, true);
		lru_cache_add_active_or_unevictable(page, vma);
		pgtable_trans_huge_deposit(vma->vm_mm, vmf->pmd, pgtable);
		set_pmd_at(vma->vm_mm, haddr, vmf->pmd, entry);
		add_mm_counter(vma->vm_mm, MM_ANONPAGES, HPAGE_PMD_NR);
		mm_inc_nr_ptes(vma->vm_mm);
		spin_unlock(vmf->ptl);
		count_vm_event(THP_FAULT_ALLOC);
		count_memcg_events(memcg, THP_FAULT_ALLOC, 1);
	}

	return 0;
unlock_release:
	spin_unlock(vmf->ptl);
release:
	if (pgtable)
		pte_free(vma->vm_mm, pgtable);
	mem_cgroup_cancel_charge(page, memcg, true);
	put_page(page);
	return ret;

}