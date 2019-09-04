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
struct vfio_iommu_driver {TYPE_1__* ops; } ;
struct vfio_container {int /*<<< orphan*/  iommu_data; struct vfio_iommu_driver* iommu_driver; } ;
struct file {struct vfio_container* private_data; } ;
struct TYPE_2__ {int (* mmap ) (int /*<<< orphan*/ ,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int vfio_fops_mmap(struct file *filep, struct vm_area_struct *vma)
{
	struct vfio_container *container = filep->private_data;
	struct vfio_iommu_driver *driver;
	int ret = -EINVAL;

	driver = container->iommu_driver;
	if (likely(driver && driver->ops->mmap))
		ret = driver->ops->mmap(container->iommu_data, vma);

	return ret;
}