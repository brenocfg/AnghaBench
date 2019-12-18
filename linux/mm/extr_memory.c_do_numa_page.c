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
struct vm_fault {int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pte; int /*<<< orphan*/  address; int /*<<< orphan*/  orig_pte; int /*<<< orphan*/  pmd; struct vm_area_struct* vma; } ;
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_mm; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 scalar_t__ PageCompound (struct page*) ; 
 int TNF_MIGRATED ; 
 int TNF_MIGRATE_FAIL ; 
 int TNF_NO_GROUP ; 
 int TNF_SHARED ; 
 int VM_SHARED ; 
 int migrate_misplaced_page (struct page*,struct vm_area_struct*,int) ; 
 int numa_migrate_prep (struct page*,struct vm_area_struct*,int /*<<< orphan*/ ,int,int*) ; 
 int page_cpupid_last (struct page*) ; 
 int page_mapcount (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  pte_lockptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pte_savedwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_modify_prot_commit (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_modify_prot_start (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_numa_fault (int,int,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* vm_normal_page (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t do_numa_page(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct page *page = NULL;
	int page_nid = NUMA_NO_NODE;
	int last_cpupid;
	int target_nid;
	bool migrated = false;
	pte_t pte, old_pte;
	bool was_writable = pte_savedwrite(vmf->orig_pte);
	int flags = 0;

	/*
	 * The "pte" at this point cannot be used safely without
	 * validation through pte_unmap_same(). It's of NUMA type but
	 * the pfn may be screwed if the read is non atomic.
	 */
	vmf->ptl = pte_lockptr(vma->vm_mm, vmf->pmd);
	spin_lock(vmf->ptl);
	if (unlikely(!pte_same(*vmf->pte, vmf->orig_pte))) {
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		goto out;
	}

	/*
	 * Make it present again, Depending on how arch implementes non
	 * accessible ptes, some can allow access by kernel mode.
	 */
	old_pte = ptep_modify_prot_start(vma, vmf->address, vmf->pte);
	pte = pte_modify(old_pte, vma->vm_page_prot);
	pte = pte_mkyoung(pte);
	if (was_writable)
		pte = pte_mkwrite(pte);
	ptep_modify_prot_commit(vma, vmf->address, vmf->pte, old_pte, pte);
	update_mmu_cache(vma, vmf->address, vmf->pte);

	page = vm_normal_page(vma, vmf->address, pte);
	if (!page) {
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		return 0;
	}

	/* TODO: handle PTE-mapped THP */
	if (PageCompound(page)) {
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		return 0;
	}

	/*
	 * Avoid grouping on RO pages in general. RO pages shouldn't hurt as
	 * much anyway since they can be in shared cache state. This misses
	 * the case where a mapping is writable but the process never writes
	 * to it but pte_write gets cleared during protection updates and
	 * pte_dirty has unpredictable behaviour between PTE scan updates,
	 * background writeback, dirty balancing and application behaviour.
	 */
	if (!pte_write(pte))
		flags |= TNF_NO_GROUP;

	/*
	 * Flag if the page is shared between multiple address spaces. This
	 * is later used when determining whether to group tasks together
	 */
	if (page_mapcount(page) > 1 && (vma->vm_flags & VM_SHARED))
		flags |= TNF_SHARED;

	last_cpupid = page_cpupid_last(page);
	page_nid = page_to_nid(page);
	target_nid = numa_migrate_prep(page, vma, vmf->address, page_nid,
			&flags);
	pte_unmap_unlock(vmf->pte, vmf->ptl);
	if (target_nid == NUMA_NO_NODE) {
		put_page(page);
		goto out;
	}

	/* Migrate to the requested node */
	migrated = migrate_misplaced_page(page, vma, target_nid);
	if (migrated) {
		page_nid = target_nid;
		flags |= TNF_MIGRATED;
	} else
		flags |= TNF_MIGRATE_FAIL;

out:
	if (page_nid != NUMA_NO_NODE)
		task_numa_fault(last_cpupid, page_nid, 1, flags);
	return 0;
}