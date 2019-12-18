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
struct vm_userfaultfd_ctx {int dummy; } ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/  anon_vma; struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;
struct mempolicy {int dummy; } ;
struct file {int dummy; } ;
struct anon_vma {int dummy; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long VM_SPECIAL ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int __vma_adjust (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 scalar_t__ can_vma_merge_after (struct vm_area_struct*,unsigned long,struct anon_vma*,struct file*,unsigned long,struct vm_userfaultfd_ctx) ; 
 scalar_t__ can_vma_merge_before (struct vm_area_struct*,unsigned long,struct anon_vma*,struct file*,unsigned long,struct vm_userfaultfd_ctx) ; 
 scalar_t__ is_mergeable_anon_vma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khugepaged_enter_vma_merge (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ mpol_equal (struct mempolicy*,struct mempolicy*) ; 
 struct mempolicy* vma_policy (struct vm_area_struct*) ; 

struct vm_area_struct *vma_merge(struct mm_struct *mm,
			struct vm_area_struct *prev, unsigned long addr,
			unsigned long end, unsigned long vm_flags,
			struct anon_vma *anon_vma, struct file *file,
			pgoff_t pgoff, struct mempolicy *policy,
			struct vm_userfaultfd_ctx vm_userfaultfd_ctx)
{
	pgoff_t pglen = (end - addr) >> PAGE_SHIFT;
	struct vm_area_struct *area, *next;
	int err;

	/*
	 * We later require that vma->vm_flags == vm_flags,
	 * so this tests vma->vm_flags & VM_SPECIAL, too.
	 */
	if (vm_flags & VM_SPECIAL)
		return NULL;

	if (prev)
		next = prev->vm_next;
	else
		next = mm->mmap;
	area = next;
	if (area && area->vm_end == end)		/* cases 6, 7, 8 */
		next = next->vm_next;

	/* verify some invariant that must be enforced by the caller */
	VM_WARN_ON(prev && addr <= prev->vm_start);
	VM_WARN_ON(area && end > area->vm_end);
	VM_WARN_ON(addr >= end);

	/*
	 * Can it merge with the predecessor?
	 */
	if (prev && prev->vm_end == addr &&
			mpol_equal(vma_policy(prev), policy) &&
			can_vma_merge_after(prev, vm_flags,
					    anon_vma, file, pgoff,
					    vm_userfaultfd_ctx)) {
		/*
		 * OK, it can.  Can we now merge in the successor as well?
		 */
		if (next && end == next->vm_start &&
				mpol_equal(policy, vma_policy(next)) &&
				can_vma_merge_before(next, vm_flags,
						     anon_vma, file,
						     pgoff+pglen,
						     vm_userfaultfd_ctx) &&
				is_mergeable_anon_vma(prev->anon_vma,
						      next->anon_vma, NULL)) {
							/* cases 1, 6 */
			err = __vma_adjust(prev, prev->vm_start,
					 next->vm_end, prev->vm_pgoff, NULL,
					 prev);
		} else					/* cases 2, 5, 7 */
			err = __vma_adjust(prev, prev->vm_start,
					 end, prev->vm_pgoff, NULL, prev);
		if (err)
			return NULL;
		khugepaged_enter_vma_merge(prev, vm_flags);
		return prev;
	}

	/*
	 * Can this new request be merged in front of next?
	 */
	if (next && end == next->vm_start &&
			mpol_equal(policy, vma_policy(next)) &&
			can_vma_merge_before(next, vm_flags,
					     anon_vma, file, pgoff+pglen,
					     vm_userfaultfd_ctx)) {
		if (prev && addr < prev->vm_end)	/* case 4 */
			err = __vma_adjust(prev, prev->vm_start,
					 addr, prev->vm_pgoff, NULL, next);
		else {					/* cases 3, 8 */
			err = __vma_adjust(area, addr, next->vm_end,
					 next->vm_pgoff - pglen, NULL, next);
			/*
			 * In case 3 area is already equal to next and
			 * this is a noop, but in case 8 "area" has
			 * been removed and next was expanded over it.
			 */
			area = next;
		}
		if (err)
			return NULL;
		khugepaged_enter_vma_merge(area, vm_flags);
		return area;
	}

	return NULL;
}