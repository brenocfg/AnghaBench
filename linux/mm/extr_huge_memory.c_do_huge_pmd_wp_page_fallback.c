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
struct vm_fault {unsigned long address; int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pmd; int /*<<< orphan*/ * pte; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HPAGE_PMD_MASK ; 
 int HPAGE_PMD_NR ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_FAULT_WRITE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_page_vma_node (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  copy_user_highpage (struct page*,struct page*,unsigned long,struct vm_area_struct*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 scalar_t__ mem_cgroup_try_charge_delay (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_only_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,int) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  pgtable_trans_huge_withdraw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_huge_clear_flush_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static vm_fault_t do_huge_pmd_wp_page_fallback(struct vm_fault *vmf,
			pmd_t orig_pmd, struct page *page)
{
	struct vm_area_struct *vma = vmf->vma;
	unsigned long haddr = vmf->address & HPAGE_PMD_MASK;
	struct mem_cgroup *memcg;
	pgtable_t pgtable;
	pmd_t _pmd;
	int i;
	vm_fault_t ret = 0;
	struct page **pages;
	struct mmu_notifier_range range;

	pages = kmalloc_array(HPAGE_PMD_NR, sizeof(struct page *),
			      GFP_KERNEL);
	if (unlikely(!pages)) {
		ret |= VM_FAULT_OOM;
		goto out;
	}

	for (i = 0; i < HPAGE_PMD_NR; i++) {
		pages[i] = alloc_page_vma_node(GFP_HIGHUSER_MOVABLE, vma,
					       vmf->address, page_to_nid(page));
		if (unlikely(!pages[i] ||
			     mem_cgroup_try_charge_delay(pages[i], vma->vm_mm,
				     GFP_KERNEL, &memcg, false))) {
			if (pages[i])
				put_page(pages[i]);
			while (--i >= 0) {
				memcg = (void *)page_private(pages[i]);
				set_page_private(pages[i], 0);
				mem_cgroup_cancel_charge(pages[i], memcg,
						false);
				put_page(pages[i]);
			}
			kfree(pages);
			ret |= VM_FAULT_OOM;
			goto out;
		}
		set_page_private(pages[i], (unsigned long)memcg);
	}

	for (i = 0; i < HPAGE_PMD_NR; i++) {
		copy_user_highpage(pages[i], page + i,
				   haddr + PAGE_SIZE * i, vma);
		__SetPageUptodate(pages[i]);
		cond_resched();
	}

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				haddr, haddr + HPAGE_PMD_SIZE);
	mmu_notifier_invalidate_range_start(&range);

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	if (unlikely(!pmd_same(*vmf->pmd, orig_pmd)))
		goto out_free_pages;
	VM_BUG_ON_PAGE(!PageHead(page), page);

	/*
	 * Leave pmd empty until pte is filled note we must notify here as
	 * concurrent CPU thread might write to new page before the call to
	 * mmu_notifier_invalidate_range_end() happens which can lead to a
	 * device seeing memory write in different order than CPU.
	 *
	 * See Documentation/vm/mmu_notifier.rst
	 */
	pmdp_huge_clear_flush_notify(vma, haddr, vmf->pmd);

	pgtable = pgtable_trans_huge_withdraw(vma->vm_mm, vmf->pmd);
	pmd_populate(vma->vm_mm, &_pmd, pgtable);

	for (i = 0; i < HPAGE_PMD_NR; i++, haddr += PAGE_SIZE) {
		pte_t entry;
		entry = mk_pte(pages[i], vma->vm_page_prot);
		entry = maybe_mkwrite(pte_mkdirty(entry), vma);
		memcg = (void *)page_private(pages[i]);
		set_page_private(pages[i], 0);
		page_add_new_anon_rmap(pages[i], vmf->vma, haddr, false);
		mem_cgroup_commit_charge(pages[i], memcg, false, false);
		lru_cache_add_active_or_unevictable(pages[i], vma);
		vmf->pte = pte_offset_map(&_pmd, haddr);
		VM_BUG_ON(!pte_none(*vmf->pte));
		set_pte_at(vma->vm_mm, haddr, vmf->pte, entry);
		pte_unmap(vmf->pte);
	}
	kfree(pages);

	smp_wmb(); /* make pte visible before pmd */
	pmd_populate(vma->vm_mm, vmf->pmd, pgtable);
	page_remove_rmap(page, true);
	spin_unlock(vmf->ptl);

	/*
	 * No need to double call mmu_notifier->invalidate_range() callback as
	 * the above pmdp_huge_clear_flush_notify() did already call it.
	 */
	mmu_notifier_invalidate_range_only_end(&range);

	ret |= VM_FAULT_WRITE;
	put_page(page);

out:
	return ret;

out_free_pages:
	spin_unlock(vmf->ptl);
	mmu_notifier_invalidate_range_end(&range);
	for (i = 0; i < HPAGE_PMD_NR; i++) {
		memcg = (void *)page_private(pages[i]);
		set_page_private(pages[i], 0);
		mem_cgroup_cancel_charge(pages[i], memcg, false);
		put_page(pages[i]);
	}
	kfree(pages);
	goto out;
}