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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {TYPE_1__* vm_file; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
struct hstate {unsigned long order; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  adjust_range_if_pmd_sharing_possible (struct vm_area_struct*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  arch_make_huge_pte (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_hugetlb_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 scalar_t__ huge_page_size (struct hstate*) ; 
 scalar_t__ huge_pmd_unshare (struct mm_struct*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * huge_pte_lock (struct hstate*,struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_pte_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ptep_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_mmap_lock_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_mmap_unlock_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hugetlb_entry_hwpoisoned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hugetlb_entry_migration (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_migration_entry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pte_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_swap_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

unsigned long hugetlb_change_protection(struct vm_area_struct *vma,
		unsigned long address, unsigned long end, pgprot_t newprot)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long start = address;
	pte_t *ptep;
	pte_t pte;
	struct hstate *h = hstate_vma(vma);
	unsigned long pages = 0;
	unsigned long f_start = start;
	unsigned long f_end = end;
	bool shared_pmd = false;

	/*
	 * In the case of shared PMDs, the area to flush could be beyond
	 * start/end.  Set f_start/f_end to cover the maximum possible
	 * range if PMD sharing is possible.
	 */
	adjust_range_if_pmd_sharing_possible(vma, &f_start, &f_end);

	BUG_ON(address >= end);
	flush_cache_range(vma, f_start, f_end);

	mmu_notifier_invalidate_range_start(mm, f_start, f_end);
	i_mmap_lock_write(vma->vm_file->f_mapping);
	for (; address < end; address += huge_page_size(h)) {
		spinlock_t *ptl;
		ptep = huge_pte_offset(mm, address, huge_page_size(h));
		if (!ptep)
			continue;
		ptl = huge_pte_lock(h, mm, ptep);
		if (huge_pmd_unshare(mm, &address, ptep)) {
			pages++;
			spin_unlock(ptl);
			shared_pmd = true;
			continue;
		}
		pte = huge_ptep_get(ptep);
		if (unlikely(is_hugetlb_entry_hwpoisoned(pte))) {
			spin_unlock(ptl);
			continue;
		}
		if (unlikely(is_hugetlb_entry_migration(pte))) {
			swp_entry_t entry = pte_to_swp_entry(pte);

			if (is_write_migration_entry(entry)) {
				pte_t newpte;

				make_migration_entry_read(&entry);
				newpte = swp_entry_to_pte(entry);
				set_huge_swap_pte_at(mm, address, ptep,
						     newpte, huge_page_size(h));
				pages++;
			}
			spin_unlock(ptl);
			continue;
		}
		if (!huge_pte_none(pte)) {
			pte = huge_ptep_get_and_clear(mm, address, ptep);
			pte = pte_mkhuge(huge_pte_modify(pte, newprot));
			pte = arch_make_huge_pte(pte, vma, NULL, 0);
			set_huge_pte_at(mm, address, ptep, pte);
			pages++;
		}
		spin_unlock(ptl);
	}
	/*
	 * Must flush TLB before releasing i_mmap_rwsem: x86's huge_pmd_unshare
	 * may have cleared our pud entry and done put_page on the page table:
	 * once we release i_mmap_rwsem, another task can do the final put_page
	 * and that page table be reused and filled with junk.  If we actually
	 * did unshare a page of pmds, flush the range corresponding to the pud.
	 */
	if (shared_pmd)
		flush_hugetlb_tlb_range(vma, f_start, f_end);
	else
		flush_hugetlb_tlb_range(vma, start, end);
	/*
	 * No need to call mmu_notifier_invalidate_range() we are downgrading
	 * page table protection not changing it to point to a new page.
	 *
	 * See Documentation/vm/mmu_notifier.rst
	 */
	i_mmap_unlock_write(vma->vm_file->f_mapping);
	mmu_notifier_invalidate_range_end(mm, f_start, f_end);

	return pages << h->order;
}