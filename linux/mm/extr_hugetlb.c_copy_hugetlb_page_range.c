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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
struct mm_struct {int dummy; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int VM_MAYWRITE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 unsigned long huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/ * huge_pte_alloc (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * huge_pte_lock (struct hstate*,struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * huge_pte_lockptr (struct hstate*,struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ptep_set_wrprotect (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hugetlb_count_add (int /*<<< orphan*/ ,struct mm_struct*) ; 
 scalar_t__ is_hugetlb_entry_hwpoisoned (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hugetlb_entry_migration (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_migration_entry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*,int) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_swap_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int copy_hugetlb_page_range(struct mm_struct *dst, struct mm_struct *src,
			    struct vm_area_struct *vma)
{
	pte_t *src_pte, *dst_pte, entry, dst_entry;
	struct page *ptepage;
	unsigned long addr;
	int cow;
	struct hstate *h = hstate_vma(vma);
	unsigned long sz = huge_page_size(h);
	struct mmu_notifier_range range;
	int ret = 0;

	cow = (vma->vm_flags & (VM_SHARED | VM_MAYWRITE)) == VM_MAYWRITE;

	if (cow) {
		mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, src,
					vma->vm_start,
					vma->vm_end);
		mmu_notifier_invalidate_range_start(&range);
	}

	for (addr = vma->vm_start; addr < vma->vm_end; addr += sz) {
		spinlock_t *src_ptl, *dst_ptl;
		src_pte = huge_pte_offset(src, addr, sz);
		if (!src_pte)
			continue;
		dst_pte = huge_pte_alloc(dst, addr, sz);
		if (!dst_pte) {
			ret = -ENOMEM;
			break;
		}

		/*
		 * If the pagetables are shared don't copy or take references.
		 * dst_pte == src_pte is the common case of src/dest sharing.
		 *
		 * However, src could have 'unshared' and dst shares with
		 * another vma.  If dst_pte !none, this implies sharing.
		 * Check here before taking page table lock, and once again
		 * after taking the lock below.
		 */
		dst_entry = huge_ptep_get(dst_pte);
		if ((dst_pte == src_pte) || !huge_pte_none(dst_entry))
			continue;

		dst_ptl = huge_pte_lock(h, dst, dst_pte);
		src_ptl = huge_pte_lockptr(h, src, src_pte);
		spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);
		entry = huge_ptep_get(src_pte);
		dst_entry = huge_ptep_get(dst_pte);
		if (huge_pte_none(entry) || !huge_pte_none(dst_entry)) {
			/*
			 * Skip if src entry none.  Also, skip in the
			 * unlikely case dst entry !none as this implies
			 * sharing with another vma.
			 */
			;
		} else if (unlikely(is_hugetlb_entry_migration(entry) ||
				    is_hugetlb_entry_hwpoisoned(entry))) {
			swp_entry_t swp_entry = pte_to_swp_entry(entry);

			if (is_write_migration_entry(swp_entry) && cow) {
				/*
				 * COW mappings require pages in both
				 * parent and child to be set to read.
				 */
				make_migration_entry_read(&swp_entry);
				entry = swp_entry_to_pte(swp_entry);
				set_huge_swap_pte_at(src, addr, src_pte,
						     entry, sz);
			}
			set_huge_swap_pte_at(dst, addr, dst_pte, entry, sz);
		} else {
			if (cow) {
				/*
				 * No need to notify as we are downgrading page
				 * table protection not changing it to point
				 * to a new page.
				 *
				 * See Documentation/vm/mmu_notifier.rst
				 */
				huge_ptep_set_wrprotect(src, addr, src_pte);
			}
			entry = huge_ptep_get(src_pte);
			ptepage = pte_page(entry);
			get_page(ptepage);
			page_dup_rmap(ptepage, true);
			set_huge_pte_at(dst, addr, dst_pte, entry);
			hugetlb_count_add(pages_per_huge_page(h), dst);
		}
		spin_unlock(src_ptl);
		spin_unlock(dst_ptl);
	}

	if (cow)
		mmu_notifier_invalidate_range_end(&range);

	return ret;
}