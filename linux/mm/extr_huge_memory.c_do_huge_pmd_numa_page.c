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
struct vm_fault {unsigned long address; int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pmd; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct anon_vma {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  NUMA_HINT_FAULTS ; 
 int /*<<< orphan*/  NUMA_HINT_FAULTS_LOCAL ; 
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int TNF_FAULT_LOCAL ; 
 int TNF_MIGRATED ; 
 int TNF_MIGRATE_FAIL ; 
 int TNF_NO_GROUP ; 
 int /*<<< orphan*/  count_vm_numa_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  get_page_unless_zero (struct page*) ; 
 int is_huge_zero_page (struct page*) ; 
 int migrate_misplaced_transhuge_page (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,struct page*,int) ; 
 scalar_t__ mm_tlb_flush_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range (int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 int mpol_misplaced (struct page*,struct vm_area_struct*,unsigned long) ; 
 int numa_node_id () ; 
 int page_cpupid_last (struct page*) ; 
 struct anon_vma* page_lock_anon_vma_read (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  page_unlock_anon_vma_read (struct anon_vma*) ; 
 int /*<<< orphan*/  pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmd_savedwrite (int /*<<< orphan*/ ) ; 
 int pmd_trans_migrating (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_and_wait_on_page_locked (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pmd_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_numa_fault (int,int,int /*<<< orphan*/ ,int) ; 
 int trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_mmu_cache_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

vm_fault_t do_huge_pmd_numa_page(struct vm_fault *vmf, pmd_t pmd)
{
	struct vm_area_struct *vma = vmf->vma;
	struct anon_vma *anon_vma = NULL;
	struct page *page;
	unsigned long haddr = vmf->address & HPAGE_PMD_MASK;
	int page_nid = NUMA_NO_NODE, this_nid = numa_node_id();
	int target_nid, last_cpupid = -1;
	bool page_locked;
	bool migrated = false;
	bool was_writable;
	int flags = 0;

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	if (unlikely(!pmd_same(pmd, *vmf->pmd)))
		goto out_unlock;

	/*
	 * If there are potential migrations, wait for completion and retry
	 * without disrupting NUMA hinting information. Do not relock and
	 * check_same as the page may no longer be mapped.
	 */
	if (unlikely(pmd_trans_migrating(*vmf->pmd))) {
		page = pmd_page(*vmf->pmd);
		if (!get_page_unless_zero(page))
			goto out_unlock;
		spin_unlock(vmf->ptl);
		put_and_wait_on_page_locked(page);
		goto out;
	}

	page = pmd_page(pmd);
	BUG_ON(is_huge_zero_page(page));
	page_nid = page_to_nid(page);
	last_cpupid = page_cpupid_last(page);
	count_vm_numa_event(NUMA_HINT_FAULTS);
	if (page_nid == this_nid) {
		count_vm_numa_event(NUMA_HINT_FAULTS_LOCAL);
		flags |= TNF_FAULT_LOCAL;
	}

	/* See similar comment in do_numa_page for explanation */
	if (!pmd_savedwrite(pmd))
		flags |= TNF_NO_GROUP;

	/*
	 * Acquire the page lock to serialise THP migrations but avoid dropping
	 * page_table_lock if at all possible
	 */
	page_locked = trylock_page(page);
	target_nid = mpol_misplaced(page, vma, haddr);
	if (target_nid == NUMA_NO_NODE) {
		/* If the page was locked, there are no parallel migrations */
		if (page_locked)
			goto clear_pmdnuma;
	}

	/* Migration could have started since the pmd_trans_migrating check */
	if (!page_locked) {
		page_nid = NUMA_NO_NODE;
		if (!get_page_unless_zero(page))
			goto out_unlock;
		spin_unlock(vmf->ptl);
		put_and_wait_on_page_locked(page);
		goto out;
	}

	/*
	 * Page is misplaced. Page lock serialises migrations. Acquire anon_vma
	 * to serialises splits
	 */
	get_page(page);
	spin_unlock(vmf->ptl);
	anon_vma = page_lock_anon_vma_read(page);

	/* Confirm the PMD did not change while page_table_lock was released */
	spin_lock(vmf->ptl);
	if (unlikely(!pmd_same(pmd, *vmf->pmd))) {
		unlock_page(page);
		put_page(page);
		page_nid = NUMA_NO_NODE;
		goto out_unlock;
	}

	/* Bail if we fail to protect against THP splits for any reason */
	if (unlikely(!anon_vma)) {
		put_page(page);
		page_nid = NUMA_NO_NODE;
		goto clear_pmdnuma;
	}

	/*
	 * Since we took the NUMA fault, we must have observed the !accessible
	 * bit. Make sure all other CPUs agree with that, to avoid them
	 * modifying the page we're about to migrate.
	 *
	 * Must be done under PTL such that we'll observe the relevant
	 * inc_tlb_flush_pending().
	 *
	 * We are not sure a pending tlb flush here is for a huge page
	 * mapping or not. Hence use the tlb range variant
	 */
	if (mm_tlb_flush_pending(vma->vm_mm)) {
		flush_tlb_range(vma, haddr, haddr + HPAGE_PMD_SIZE);
		/*
		 * change_huge_pmd() released the pmd lock before
		 * invalidating the secondary MMUs sharing the primary
		 * MMU pagetables (with ->invalidate_range()). The
		 * mmu_notifier_invalidate_range_end() (which
		 * internally calls ->invalidate_range()) in
		 * change_pmd_range() will run after us, so we can't
		 * rely on it here and we need an explicit invalidate.
		 */
		mmu_notifier_invalidate_range(vma->vm_mm, haddr,
					      haddr + HPAGE_PMD_SIZE);
	}

	/*
	 * Migrate the THP to the requested node, returns with page unlocked
	 * and access rights restored.
	 */
	spin_unlock(vmf->ptl);

	migrated = migrate_misplaced_transhuge_page(vma->vm_mm, vma,
				vmf->pmd, pmd, vmf->address, page, target_nid);
	if (migrated) {
		flags |= TNF_MIGRATED;
		page_nid = target_nid;
	} else
		flags |= TNF_MIGRATE_FAIL;

	goto out;
clear_pmdnuma:
	BUG_ON(!PageLocked(page));
	was_writable = pmd_savedwrite(pmd);
	pmd = pmd_modify(pmd, vma->vm_page_prot);
	pmd = pmd_mkyoung(pmd);
	if (was_writable)
		pmd = pmd_mkwrite(pmd);
	set_pmd_at(vma->vm_mm, haddr, vmf->pmd, pmd);
	update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
	unlock_page(page);
out_unlock:
	spin_unlock(vmf->ptl);

out:
	if (anon_vma)
		page_unlock_anon_vma_read(anon_vma);

	if (page_nid != NUMA_NO_NODE)
		task_numa_fault(last_cpupid, page_nid, HPAGE_PMD_NR,
				flags);

	return 0;
}