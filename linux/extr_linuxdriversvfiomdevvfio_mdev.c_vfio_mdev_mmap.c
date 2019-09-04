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
struct vm_area_struct {int dummy; } ;
struct mdev_parent {TYPE_1__* ops; } ;
struct mdev_device {struct mdev_parent* parent; } ;
struct TYPE_2__ {int (* mmap ) (struct mdev_device*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct mdev_device*,struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vfio_mdev_mmap(void *device_data, struct vm_area_struct *vma)
{
	struct mdev_device *mdev = device_data;
	struct mdev_parent *parent = mdev->parent;

	if (unlikely(!parent->ops->mmap))
		return -EINVAL;

	return parent->ops->mmap(mdev, vma);
}