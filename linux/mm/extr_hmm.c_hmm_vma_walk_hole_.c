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
typedef  int /*<<< orphan*/  uint64_t ;
struct mm_walk {TYPE_1__* vma; struct hmm_vma_walk* private; } ;
struct hmm_vma_walk {unsigned long last; struct hmm_range* range; } ;
struct hmm_range {unsigned long start; int /*<<< orphan*/ * values; int /*<<< orphan*/ * pfns; } ;
struct TYPE_2__ {int vm_flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 size_t HMM_PFN_NONE ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_WRITE ; 
 int hmm_vma_do_fault (struct mm_walk*,unsigned long,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hmm_vma_walk_hole_(unsigned long addr, unsigned long end,
			      bool fault, bool write_fault,
			      struct mm_walk *walk)
{
	struct hmm_vma_walk *hmm_vma_walk = walk->private;
	struct hmm_range *range = hmm_vma_walk->range;
	uint64_t *pfns = range->pfns;
	unsigned long i;

	hmm_vma_walk->last = addr;
	i = (addr - range->start) >> PAGE_SHIFT;

	if (write_fault && walk->vma && !(walk->vma->vm_flags & VM_WRITE))
		return -EPERM;

	for (; addr < end; addr += PAGE_SIZE, i++) {
		pfns[i] = range->values[HMM_PFN_NONE];
		if (fault || write_fault) {
			int ret;

			ret = hmm_vma_do_fault(walk, addr, write_fault,
					       &pfns[i]);
			if (ret != -EBUSY)
				return ret;
		}
	}

	return (fault || write_fault) ? -EBUSY : 0;
}