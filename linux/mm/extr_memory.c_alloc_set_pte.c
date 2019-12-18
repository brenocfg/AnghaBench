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
typedef  scalar_t__ vm_fault_t ;
struct vm_fault {int flags; int /*<<< orphan*/ * pte; int /*<<< orphan*/  address; int /*<<< orphan*/ * pmd; struct vm_area_struct* vma; } ;
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TRANSPARENT_HUGE_PAGECACHE ; 
 int FAULT_FLAG_WRITE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (struct mem_cgroup*,struct page*) ; 
 scalar_t__ VM_FAULT_FALLBACK ; 
 scalar_t__ VM_FAULT_NOPAGE ; 
 int VM_SHARED ; 
 scalar_t__ do_set_pmd (struct vm_fault*,struct page*) ; 
 int /*<<< orphan*/  flush_icache_page (struct vm_area_struct*,struct page*) ; 
 int /*<<< orphan*/  inc_mm_counter_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_counter_file (struct page*) ; 
 int /*<<< orphan*/  page_add_file_rmap (struct page*,int) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_alloc_one_map (struct vm_fault*) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

vm_fault_t alloc_set_pte(struct vm_fault *vmf, struct mem_cgroup *memcg,
		struct page *page)
{
	struct vm_area_struct *vma = vmf->vma;
	bool write = vmf->flags & FAULT_FLAG_WRITE;
	pte_t entry;
	vm_fault_t ret;

	if (pmd_none(*vmf->pmd) && PageTransCompound(page) &&
			IS_ENABLED(CONFIG_TRANSPARENT_HUGE_PAGECACHE)) {
		/* THP on COW? */
		VM_BUG_ON_PAGE(memcg, page);

		ret = do_set_pmd(vmf, page);
		if (ret != VM_FAULT_FALLBACK)
			return ret;
	}

	if (!vmf->pte) {
		ret = pte_alloc_one_map(vmf);
		if (ret)
			return ret;
	}

	/* Re-check under ptl */
	if (unlikely(!pte_none(*vmf->pte)))
		return VM_FAULT_NOPAGE;

	flush_icache_page(vma, page);
	entry = mk_pte(page, vma->vm_page_prot);
	if (write)
		entry = maybe_mkwrite(pte_mkdirty(entry), vma);
	/* copy-on-write page */
	if (write && !(vma->vm_flags & VM_SHARED)) {
		inc_mm_counter_fast(vma->vm_mm, MM_ANONPAGES);
		page_add_new_anon_rmap(page, vma, vmf->address, false);
		mem_cgroup_commit_charge(page, memcg, false, false);
		lru_cache_add_active_or_unevictable(page, vma);
	} else {
		inc_mm_counter_fast(vma->vm_mm, mm_counter_file(page));
		page_add_file_rmap(page, false);
	}
	set_pte_at(vma->vm_mm, vmf->address, vmf->pte, entry);

	/* no need to invalidate: a not-present page won't be cached */
	update_mmu_cache(vma, vmf->address, vmf->pte);

	return 0;
}