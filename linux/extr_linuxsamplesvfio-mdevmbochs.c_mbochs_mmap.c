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
struct vm_area_struct {scalar_t__ vm_pgoff; scalar_t__ vm_end; scalar_t__ vm_start; int vm_flags; struct mdev_state* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct mdev_state {scalar_t__ memsize; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MBOCHS_MEMORY_BAR_OFFSET ; 
 int PAGE_SHIFT ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  mbochs_region_vm_ops ; 
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 

__attribute__((used)) static int mbochs_mmap(struct mdev_device *mdev, struct vm_area_struct *vma)
{
	struct mdev_state *mdev_state = mdev_get_drvdata(mdev);

	if (vma->vm_pgoff != MBOCHS_MEMORY_BAR_OFFSET >> PAGE_SHIFT)
		return -EINVAL;
	if (vma->vm_end < vma->vm_start)
		return -EINVAL;
	if (vma->vm_end - vma->vm_start > mdev_state->memsize)
		return -EINVAL;
	if ((vma->vm_flags & VM_SHARED) == 0)
		return -EINVAL;

	vma->vm_ops = &mbochs_region_vm_ops;
	vma->vm_private_data = mdev_state;
	return 0;
}