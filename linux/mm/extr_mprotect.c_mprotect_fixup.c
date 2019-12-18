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
struct vm_area_struct {unsigned long vm_flags; unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_userfaultfd_ctx; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  anon_vma; scalar_t__ vm_pgoff; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long VM_ACCOUNT ; 
 unsigned long VM_EXEC ; 
 unsigned long VM_HUGETLB ; 
 unsigned long VM_LOCKED ; 
 int VM_MIXEDMAP ; 
 unsigned long VM_NORESERVE ; 
 int VM_PFNMAP ; 
 unsigned long VM_READ ; 
 unsigned long VM_SHARED ; 
 unsigned long VM_SOFTDIRTY ; 
 int /*<<< orphan*/  VM_WARN_ON (unsigned long) ; 
 unsigned long VM_WRITE ; 
 scalar_t__ arch_has_pfn_modify_check () ; 
 int /*<<< orphan*/  change_protection (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 scalar_t__ may_expand_vm (struct mm_struct*,unsigned long,long) ; 
 int /*<<< orphan*/  perf_event_mmap (struct vm_area_struct*) ; 
 int /*<<< orphan*/  populate_vma_page_range (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prot_none_walk_ops ; 
 scalar_t__ security_vm_enough_memory_mm (struct mm_struct*,unsigned long) ; 
 int split_vma (struct mm_struct*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  vm_get_page_prot (unsigned long) ; 
 int /*<<< orphan*/  vm_stat_account (struct mm_struct*,unsigned long,long) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_set_page_prot (struct vm_area_struct*) ; 
 int vma_wants_writenotify (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int walk_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mprotect_fixup(struct vm_area_struct *vma, struct vm_area_struct **pprev,
	unsigned long start, unsigned long end, unsigned long newflags)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long oldflags = vma->vm_flags;
	long nrpages = (end - start) >> PAGE_SHIFT;
	unsigned long charged = 0;
	pgoff_t pgoff;
	int error;
	int dirty_accountable = 0;

	if (newflags == oldflags) {
		*pprev = vma;
		return 0;
	}

	/*
	 * Do PROT_NONE PFN permission checks here when we can still
	 * bail out without undoing a lot of state. This is a rather
	 * uncommon case, so doesn't need to be very optimized.
	 */
	if (arch_has_pfn_modify_check() &&
	    (vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) &&
	    (newflags & (VM_READ|VM_WRITE|VM_EXEC)) == 0) {
		pgprot_t new_pgprot = vm_get_page_prot(newflags);

		error = walk_page_range(current->mm, start, end,
				&prot_none_walk_ops, &new_pgprot);
		if (error)
			return error;
	}

	/*
	 * If we make a private mapping writable we increase our commit;
	 * but (without finer accounting) cannot reduce our commit if we
	 * make it unwritable again. hugetlb mapping were accounted for
	 * even if read-only so there is no need to account for them here
	 */
	if (newflags & VM_WRITE) {
		/* Check space limits when area turns into data. */
		if (!may_expand_vm(mm, newflags, nrpages) &&
				may_expand_vm(mm, oldflags, nrpages))
			return -ENOMEM;
		if (!(oldflags & (VM_ACCOUNT|VM_WRITE|VM_HUGETLB|
						VM_SHARED|VM_NORESERVE))) {
			charged = nrpages;
			if (security_vm_enough_memory_mm(mm, charged))
				return -ENOMEM;
			newflags |= VM_ACCOUNT;
		}
	}

	/*
	 * First try to merge with previous and/or next vma.
	 */
	pgoff = vma->vm_pgoff + ((start - vma->vm_start) >> PAGE_SHIFT);
	*pprev = vma_merge(mm, *pprev, start, end, newflags,
			   vma->anon_vma, vma->vm_file, pgoff, vma_policy(vma),
			   vma->vm_userfaultfd_ctx);
	if (*pprev) {
		vma = *pprev;
		VM_WARN_ON((vma->vm_flags ^ newflags) & ~VM_SOFTDIRTY);
		goto success;
	}

	*pprev = vma;

	if (start != vma->vm_start) {
		error = split_vma(mm, vma, start, 1);
		if (error)
			goto fail;
	}

	if (end != vma->vm_end) {
		error = split_vma(mm, vma, end, 0);
		if (error)
			goto fail;
	}

success:
	/*
	 * vm_flags and vm_page_prot are protected by the mmap_sem
	 * held in write mode.
	 */
	vma->vm_flags = newflags;
	dirty_accountable = vma_wants_writenotify(vma, vma->vm_page_prot);
	vma_set_page_prot(vma);

	change_protection(vma, start, end, vma->vm_page_prot,
			  dirty_accountable, 0);

	/*
	 * Private VM_LOCKED VMA becoming writable: trigger COW to avoid major
	 * fault on access.
	 */
	if ((oldflags & (VM_WRITE | VM_SHARED | VM_LOCKED)) == VM_LOCKED &&
			(newflags & VM_WRITE)) {
		populate_vma_page_range(vma, start, end, NULL);
	}

	vm_stat_account(mm, oldflags, -nrpages);
	vm_stat_account(mm, newflags, nrpages);
	perf_event_mmap(vma);
	return 0;

fail:
	vm_unacct_memory(charged);
	return error;
}