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
struct vm_area_struct {scalar_t__ vm_pgoff; scalar_t__ vm_end; scalar_t__ vm_start; int vm_flags; } ;
struct mdev_state {scalar_t__ memsize; int /*<<< orphan*/  memblk; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MDPY_MEMORY_BAR_OFFSET ; 
 int PAGE_SHIFT ; 
 int VM_SHARED ; 
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 
 int remap_vmalloc_range_partial (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mdpy_mmap(struct mdev_device *mdev, struct vm_area_struct *vma)
{
	struct mdev_state *mdev_state = mdev_get_drvdata(mdev);

	if (vma->vm_pgoff != MDPY_MEMORY_BAR_OFFSET >> PAGE_SHIFT)
		return -EINVAL;
	if (vma->vm_end < vma->vm_start)
		return -EINVAL;
	if (vma->vm_end - vma->vm_start > mdev_state->memsize)
		return -EINVAL;
	if ((vma->vm_flags & VM_SHARED) == 0)
		return -EINVAL;

	return remap_vmalloc_range_partial(vma, vma->vm_start,
					   mdev_state->memblk,
					   vma->vm_end - vma->vm_start);
}