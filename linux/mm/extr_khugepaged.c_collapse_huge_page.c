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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  anon_vma; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HPAGE_PMD_MASK ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int SCAN_ALLOC_HUGE_PAGE_FAIL ; 
 int SCAN_ANY_PROCESS ; 
 int SCAN_CGROUP_CHARGE_FAIL ; 
 int SCAN_FAIL ; 
 int SCAN_PMD_NULL ; 
 int SCAN_SUCCEED ; 
 int /*<<< orphan*/  THP_COLLAPSE_ALLOC ; 
 int /*<<< orphan*/  VM_BUG_ON (unsigned long) ; 
 int __GFP_THISNODE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __collapse_huge_page_copy (int /*<<< orphan*/ *,struct page*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int __collapse_huge_page_isolate (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __collapse_huge_page_swapin (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int alloc_hugepage_khugepaged_gfpmask () ; 
 int /*<<< orphan*/  anon_vma_lock_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anon_vma_unlock_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_memcg_events (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int hugepage_vma_revalidate (struct mm_struct*,unsigned long,struct vm_area_struct**) ; 
 struct page* khugepaged_alloc_page (struct page**,int,int) ; 
 int /*<<< orphan*/  khugepaged_pages_collapsed ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  maybe_pmd_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 int mem_cgroup_try_charge (struct page*,struct mm_struct*,int,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  mk_huge_pmd (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mm_find_pmd (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  mmget_still_valid (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  pgtable_trans_huge_deposit (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_pgtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_collapse_flush (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_collapse_huge_page (struct mm_struct*,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_mmu_cache_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void collapse_huge_page(struct mm_struct *mm,
				   unsigned long address,
				   struct page **hpage,
				   int node, int referenced)
{
	pmd_t *pmd, _pmd;
	pte_t *pte;
	pgtable_t pgtable;
	struct page *new_page;
	spinlock_t *pmd_ptl, *pte_ptl;
	int isolated = 0, result = 0;
	struct mem_cgroup *memcg;
	struct vm_area_struct *vma;
	struct mmu_notifier_range range;
	gfp_t gfp;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);

	/* Only allocate from the target node */
	gfp = alloc_hugepage_khugepaged_gfpmask() | __GFP_THISNODE;

	/*
	 * Before allocating the hugepage, release the mmap_sem read lock.
	 * The allocation can take potentially a long time if it involves
	 * sync compaction, and we do not need to hold the mmap_sem during
	 * that. We will recheck the vma after taking it again in write mode.
	 */
	up_read(&mm->mmap_sem);
	new_page = khugepaged_alloc_page(hpage, gfp, node);
	if (!new_page) {
		result = SCAN_ALLOC_HUGE_PAGE_FAIL;
		goto out_nolock;
	}

	if (unlikely(mem_cgroup_try_charge(new_page, mm, gfp, &memcg, true))) {
		result = SCAN_CGROUP_CHARGE_FAIL;
		goto out_nolock;
	}

	down_read(&mm->mmap_sem);
	result = hugepage_vma_revalidate(mm, address, &vma);
	if (result) {
		mem_cgroup_cancel_charge(new_page, memcg, true);
		up_read(&mm->mmap_sem);
		goto out_nolock;
	}

	pmd = mm_find_pmd(mm, address);
	if (!pmd) {
		result = SCAN_PMD_NULL;
		mem_cgroup_cancel_charge(new_page, memcg, true);
		up_read(&mm->mmap_sem);
		goto out_nolock;
	}

	/*
	 * __collapse_huge_page_swapin always returns with mmap_sem locked.
	 * If it fails, we release mmap_sem and jump out_nolock.
	 * Continuing to collapse causes inconsistency.
	 */
	if (!__collapse_huge_page_swapin(mm, vma, address, pmd, referenced)) {
		mem_cgroup_cancel_charge(new_page, memcg, true);
		up_read(&mm->mmap_sem);
		goto out_nolock;
	}

	up_read(&mm->mmap_sem);
	/*
	 * Prevent all access to pagetables with the exception of
	 * gup_fast later handled by the ptep_clear_flush and the VM
	 * handled by the anon_vma lock + PG_lock.
	 */
	down_write(&mm->mmap_sem);
	result = SCAN_ANY_PROCESS;
	if (!mmget_still_valid(mm))
		goto out;
	result = hugepage_vma_revalidate(mm, address, &vma);
	if (result)
		goto out;
	/* check if the pmd is still valid */
	if (mm_find_pmd(mm, address) != pmd)
		goto out;

	anon_vma_lock_write(vma->anon_vma);

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, NULL, mm,
				address, address + HPAGE_PMD_SIZE);
	mmu_notifier_invalidate_range_start(&range);

	pte = pte_offset_map(pmd, address);
	pte_ptl = pte_lockptr(mm, pmd);

	pmd_ptl = pmd_lock(mm, pmd); /* probably unnecessary */
	/*
	 * After this gup_fast can't run anymore. This also removes
	 * any huge TLB entry from the CPU so we won't allow
	 * huge and small TLB entries for the same virtual address
	 * to avoid the risk of CPU bugs in that area.
	 */
	_pmd = pmdp_collapse_flush(vma, address, pmd);
	spin_unlock(pmd_ptl);
	mmu_notifier_invalidate_range_end(&range);

	spin_lock(pte_ptl);
	isolated = __collapse_huge_page_isolate(vma, address, pte);
	spin_unlock(pte_ptl);

	if (unlikely(!isolated)) {
		pte_unmap(pte);
		spin_lock(pmd_ptl);
		BUG_ON(!pmd_none(*pmd));
		/*
		 * We can only use set_pmd_at when establishing
		 * hugepmds and never for establishing regular pmds that
		 * points to regular pagetables. Use pmd_populate for that
		 */
		pmd_populate(mm, pmd, pmd_pgtable(_pmd));
		spin_unlock(pmd_ptl);
		anon_vma_unlock_write(vma->anon_vma);
		result = SCAN_FAIL;
		goto out;
	}

	/*
	 * All pages are isolated and locked so anon_vma rmap
	 * can't run anymore.
	 */
	anon_vma_unlock_write(vma->anon_vma);

	__collapse_huge_page_copy(pte, new_page, vma, address, pte_ptl);
	pte_unmap(pte);
	__SetPageUptodate(new_page);
	pgtable = pmd_pgtable(_pmd);

	_pmd = mk_huge_pmd(new_page, vma->vm_page_prot);
	_pmd = maybe_pmd_mkwrite(pmd_mkdirty(_pmd), vma);

	/*
	 * spin_lock() below is not the equivalent of smp_wmb(), so
	 * this is needed to avoid the copy_huge_page writes to become
	 * visible after the set_pmd_at() write.
	 */
	smp_wmb();

	spin_lock(pmd_ptl);
	BUG_ON(!pmd_none(*pmd));
	page_add_new_anon_rmap(new_page, vma, address, true);
	mem_cgroup_commit_charge(new_page, memcg, false, true);
	count_memcg_events(memcg, THP_COLLAPSE_ALLOC, 1);
	lru_cache_add_active_or_unevictable(new_page, vma);
	pgtable_trans_huge_deposit(mm, pmd, pgtable);
	set_pmd_at(mm, address, pmd, _pmd);
	update_mmu_cache_pmd(vma, address, pmd);
	spin_unlock(pmd_ptl);

	*hpage = NULL;

	khugepaged_pages_collapsed++;
	result = SCAN_SUCCEED;
out_up_write:
	up_write(&mm->mmap_sem);
out_nolock:
	trace_mm_collapse_huge_page(mm, isolated, result);
	return;
out:
	mem_cgroup_cancel_charge(new_page, memcg, true);
	goto out_up_write;
}