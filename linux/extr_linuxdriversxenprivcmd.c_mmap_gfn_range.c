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
struct vm_area_struct {int vm_end; int /*<<< orphan*/  vm_page_prot; } ;
struct privcmd_mmap_entry {int npages; unsigned long va; int /*<<< orphan*/  mfn; } ;
struct mmap_gfn_state {unsigned long va; int /*<<< orphan*/  domain; struct vm_area_struct* vma; } ;

/* Variables and functions */
 int EINVAL ; 
 int LONG_MAX ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int xen_remap_domain_gfn_range (struct vm_area_struct*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmap_gfn_range(void *data, void *state)
{
	struct privcmd_mmap_entry *msg = data;
	struct mmap_gfn_state *st = state;
	struct vm_area_struct *vma = st->vma;
	int rc;

	/* Do not allow range to wrap the address space. */
	if ((msg->npages > (LONG_MAX >> PAGE_SHIFT)) ||
	    ((unsigned long)(msg->npages << PAGE_SHIFT) >= -st->va))
		return -EINVAL;

	/* Range chunks must be contiguous in va space. */
	if ((msg->va != st->va) ||
	    ((msg->va+(msg->npages<<PAGE_SHIFT)) > vma->vm_end))
		return -EINVAL;

	rc = xen_remap_domain_gfn_range(vma,
					msg->va & PAGE_MASK,
					msg->mfn, msg->npages,
					vma->vm_page_prot,
					st->domain, NULL);
	if (rc < 0)
		return rc;

	st->va += msg->npages << PAGE_SHIFT;

	return 0;
}