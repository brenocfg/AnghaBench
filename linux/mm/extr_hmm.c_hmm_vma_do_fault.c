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
typedef  int vm_fault_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vm_area_struct {int dummy; } ;
struct mm_walk {struct vm_area_struct* vma; struct hmm_vma_walk* private; } ;
struct hmm_vma_walk {int flags; struct hmm_range* range; } ;
struct hmm_range {int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EFAULT ; 
 unsigned int FAULT_FLAG_ALLOW_RETRY ; 
 unsigned int FAULT_FLAG_REMOTE ; 
 unsigned int FAULT_FLAG_WRITE ; 
 int HMM_FAULT_ALLOW_RETRY ; 
 size_t HMM_PFN_ERROR ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_RETRY ; 
 int handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 

__attribute__((used)) static int hmm_vma_do_fault(struct mm_walk *walk, unsigned long addr,
			    bool write_fault, uint64_t *pfn)
{
	unsigned int flags = FAULT_FLAG_REMOTE;
	struct hmm_vma_walk *hmm_vma_walk = walk->private;
	struct hmm_range *range = hmm_vma_walk->range;
	struct vm_area_struct *vma = walk->vma;
	vm_fault_t ret;

	if (!vma)
		goto err;

	if (hmm_vma_walk->flags & HMM_FAULT_ALLOW_RETRY)
		flags |= FAULT_FLAG_ALLOW_RETRY;
	if (write_fault)
		flags |= FAULT_FLAG_WRITE;

	ret = handle_mm_fault(vma, addr, flags);
	if (ret & VM_FAULT_RETRY) {
		/* Note, handle_mm_fault did up_read(&mm->mmap_sem)) */
		return -EAGAIN;
	}
	if (ret & VM_FAULT_ERROR)
		goto err;

	return -EBUSY;

err:
	*pfn = range->values[HMM_PFN_ERROR];
	return -EFAULT;
}