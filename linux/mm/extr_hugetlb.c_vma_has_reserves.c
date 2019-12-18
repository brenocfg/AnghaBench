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
struct vm_area_struct {int vm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 int VM_MAYSHARE ; 
 int VM_NORESERVE ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vma_has_reserves(struct vm_area_struct *vma, long chg)
{
	if (vma->vm_flags & VM_NORESERVE) {
		/*
		 * This address is already reserved by other process(chg == 0),
		 * so, we should decrement reserved count. Without decrementing,
		 * reserve count remains after releasing inode, because this
		 * allocated page will go into page cache and is regarded as
		 * coming from reserved pool in releasing step.  Currently, we
		 * don't have any other solution to deal with this situation
		 * properly, so add work-around here.
		 */
		if (vma->vm_flags & VM_MAYSHARE && chg == 0)
			return true;
		else
			return false;
	}

	/* Shared mappings always use reserves */
	if (vma->vm_flags & VM_MAYSHARE) {
		/*
		 * We know VM_NORESERVE is not set.  Therefore, there SHOULD
		 * be a region map for all pages.  The only situation where
		 * there is no region map is if a hole was punched via
		 * fallocate.  In this case, there really are no reverves to
		 * use.  This situation is indicated if chg != 0.
		 */
		if (chg)
			return false;
		else
			return true;
	}

	/*
	 * Only the process that called mmap() has reserves for
	 * private mappings.
	 */
	if (is_vma_resv_set(vma, HPAGE_RESV_OWNER)) {
		/*
		 * Like the shared case above, a hole punch or truncate
		 * could have been performed on the private mapping.
		 * Examine the value of chg to determine if reserves
		 * actually exist or were previously consumed.
		 * Very Subtle - The value of chg comes from a previous
		 * call to vma_needs_reserves().  The reserve map for
		 * private mappings has different (opposite) semantics
		 * than that of shared mappings.  vma_needs_reserves()
		 * has already taken this difference in semantics into
		 * account.  Therefore, the meaning of chg is the same
		 * as in the shared case above.  Code could easily be
		 * combined, but keeping it separate draws attention to
		 * subtle differences.
		 */
		if (chg)
			return false;
		else
			return true;
	}

	return false;
}