#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int vm_flags; TYPE_1__* vm_mm; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_4__ {int /*<<< orphan*/  mm_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MIGRATION ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NUMA_NO_NODE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageKsm (struct page*) ; 
 int VM_SHARED ; 
 int VM_SOFTDIRTY ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_tlb_batched_pending (TYPE_1__*) ; 
 scalar_t__ is_cow_mapping (int) ; 
 scalar_t__ is_write_device_private_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_device_private_entry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_migration_entry_read (int /*<<< orphan*/ *) ; 
 int numa_node_id () ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 int page_mapcount (struct page*) ; 
 int page_to_nid (struct page*) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mk_savedwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (TYPE_1__*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_protnone (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_soft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_swp_mksoft_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_swp_soft_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_modify_prot_commit (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_modify_prot_start (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (TYPE_1__*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long change_pte_range(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long addr, unsigned long end, pgprot_t newprot,
		int dirty_accountable, int prot_numa)
{
	pte_t *pte, oldpte;
	spinlock_t *ptl;
	unsigned long pages = 0;
	int target_node = NUMA_NO_NODE;

	/*
	 * Can be called with only the mmap_sem for reading by
	 * prot_numa so we must check the pmd isn't constantly
	 * changing from under us from pmd_none to pmd_trans_huge
	 * and/or the other way around.
	 */
	if (pmd_trans_unstable(pmd))
		return 0;

	/*
	 * The pmd points to a regular pte so the pmd can't change
	 * from under us even if the mmap_sem is only hold for
	 * reading.
	 */
	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);

	/* Get target node for single threaded private VMAs */
	if (prot_numa && !(vma->vm_flags & VM_SHARED) &&
	    atomic_read(&vma->vm_mm->mm_users) == 1)
		target_node = numa_node_id();

	flush_tlb_batched_pending(vma->vm_mm);
	arch_enter_lazy_mmu_mode();
	do {
		oldpte = *pte;
		if (pte_present(oldpte)) {
			pte_t ptent;
			bool preserve_write = prot_numa && pte_write(oldpte);

			/*
			 * Avoid trapping faults against the zero or KSM
			 * pages. See similar comment in change_huge_pmd.
			 */
			if (prot_numa) {
				struct page *page;

				page = vm_normal_page(vma, addr, oldpte);
				if (!page || PageKsm(page))
					continue;

				/* Also skip shared copy-on-write pages */
				if (is_cow_mapping(vma->vm_flags) &&
				    page_mapcount(page) != 1)
					continue;

				/*
				 * While migration can move some dirty pages,
				 * it cannot move them all from MIGRATE_ASYNC
				 * context.
				 */
				if (page_is_file_cache(page) && PageDirty(page))
					continue;

				/* Avoid TLB flush if possible */
				if (pte_protnone(oldpte))
					continue;

				/*
				 * Don't mess with PTEs if page is already on the node
				 * a single-threaded process is running on.
				 */
				if (target_node == page_to_nid(page))
					continue;
			}

			oldpte = ptep_modify_prot_start(vma, addr, pte);
			ptent = pte_modify(oldpte, newprot);
			if (preserve_write)
				ptent = pte_mk_savedwrite(ptent);

			/* Avoid taking write faults for known dirty pages */
			if (dirty_accountable && pte_dirty(ptent) &&
					(pte_soft_dirty(ptent) ||
					 !(vma->vm_flags & VM_SOFTDIRTY))) {
				ptent = pte_mkwrite(ptent);
			}
			ptep_modify_prot_commit(vma, addr, pte, oldpte, ptent);
			pages++;
		} else if (IS_ENABLED(CONFIG_MIGRATION)) {
			swp_entry_t entry = pte_to_swp_entry(oldpte);

			if (is_write_migration_entry(entry)) {
				pte_t newpte;
				/*
				 * A protection check is difficult so
				 * just be safe and disable write
				 */
				make_migration_entry_read(&entry);
				newpte = swp_entry_to_pte(entry);
				if (pte_swp_soft_dirty(oldpte))
					newpte = pte_swp_mksoft_dirty(newpte);
				set_pte_at(vma->vm_mm, addr, pte, newpte);

				pages++;
			}

			if (is_write_device_private_entry(entry)) {
				pte_t newpte;

				/*
				 * We do not preserve soft-dirtiness. See
				 * copy_one_pte() for explanation.
				 */
				make_device_private_entry_read(&entry);
				newpte = swp_entry_to_pte(entry);
				set_pte_at(vma->vm_mm, addr, pte, newpte);

				pages++;
			}
		}
	} while (pte++, addr += PAGE_SIZE, addr != end);
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(pte - 1, ptl);

	return pages;
}