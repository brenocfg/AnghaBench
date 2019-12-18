#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long const vm_flags; int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_end; } ;
struct hmm_vma_walk {unsigned long last; unsigned int flags; struct hmm_range* range; int /*<<< orphan*/ * pgmap; } ;
struct hmm_range {unsigned long start; unsigned long end; int /*<<< orphan*/ * pfns; scalar_t__ valid; struct hmm* hmm; } ;
struct TYPE_3__ {TYPE_2__* mm; } ;
struct hmm {TYPE_1__ mmu_notifier; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 long EBUSY ; 
 long EFAULT ; 
 long EPERM ; 
 long PAGE_SHIFT ; 
 unsigned long VM_IO ; 
 unsigned long VM_MIXEDMAP ; 
 unsigned long VM_PFNMAP ; 
 int VM_READ ; 
 struct vm_area_struct* find_vma (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  hmm_pfns_clear (struct hmm_range*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  hmm_walk_ops ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int walk_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *,struct hmm_vma_walk*) ; 

long hmm_range_fault(struct hmm_range *range, unsigned int flags)
{
	const unsigned long device_vma = VM_IO | VM_PFNMAP | VM_MIXEDMAP;
	unsigned long start = range->start, end;
	struct hmm_vma_walk hmm_vma_walk;
	struct hmm *hmm = range->hmm;
	struct vm_area_struct *vma;
	int ret;

	lockdep_assert_held(&hmm->mmu_notifier.mm->mmap_sem);

	do {
		/* If range is no longer valid force retry. */
		if (!range->valid)
			return -EBUSY;

		vma = find_vma(hmm->mmu_notifier.mm, start);
		if (vma == NULL || (vma->vm_flags & device_vma))
			return -EFAULT;

		if (!(vma->vm_flags & VM_READ)) {
			/*
			 * If vma do not allow read access, then assume that it
			 * does not allow write access, either. HMM does not
			 * support architecture that allow write without read.
			 */
			hmm_pfns_clear(range, range->pfns,
				range->start, range->end);
			return -EPERM;
		}

		hmm_vma_walk.pgmap = NULL;
		hmm_vma_walk.last = start;
		hmm_vma_walk.flags = flags;
		hmm_vma_walk.range = range;
		end = min(range->end, vma->vm_end);

		walk_page_range(vma->vm_mm, start, end, &hmm_walk_ops,
				&hmm_vma_walk);

		do {
			ret = walk_page_range(vma->vm_mm, start, end,
					&hmm_walk_ops, &hmm_vma_walk);
			start = hmm_vma_walk.last;

			/* Keep trying while the range is valid. */
		} while (ret == -EBUSY && range->valid);

		if (ret) {
			unsigned long i;

			i = (hmm_vma_walk.last - range->start) >> PAGE_SHIFT;
			hmm_pfns_clear(range, &range->pfns[i],
				hmm_vma_walk.last, range->end);
			return ret;
		}
		start = end;

	} while (start < range->end);

	return (hmm_vma_walk.last - range->start) >> PAGE_SHIFT;
}