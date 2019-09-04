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
struct vfio_iommu_driver {TYPE_1__* ops; } ;
struct vfio_container {void* iommu_data; struct vfio_iommu_driver* iommu_driver; } ;
struct file {struct vfio_container* private_data; } ;
struct TYPE_2__ {long (* ioctl ) (void*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long EINVAL ; 
 long VFIO_API_VERSION ; 
#define  VFIO_CHECK_EXTENSION 130 
#define  VFIO_GET_API_VERSION 129 
#define  VFIO_SET_IOMMU 128 
 long stub1 (void*,unsigned int,unsigned long) ; 
 long vfio_ioctl_check_extension (struct vfio_container*,unsigned long) ; 
 long vfio_ioctl_set_iommu (struct vfio_container*,unsigned long) ; 

__attribute__((used)) static long vfio_fops_unl_ioctl(struct file *filep,
				unsigned int cmd, unsigned long arg)
{
	struct vfio_container *container = filep->private_data;
	struct vfio_iommu_driver *driver;
	void *data;
	long ret = -EINVAL;

	if (!container)
		return ret;

	switch (cmd) {
	case VFIO_GET_API_VERSION:
		ret = VFIO_API_VERSION;
		break;
	case VFIO_CHECK_EXTENSION:
		ret = vfio_ioctl_check_extension(container, arg);
		break;
	case VFIO_SET_IOMMU:
		ret = vfio_ioctl_set_iommu(container, arg);
		break;
	default:
		driver = container->iommu_driver;
		data = container->iommu_data;

		if (driver) /* passthrough all unrecognized ioctls */
			ret = driver->ops->ioctl(data, cmd, arg);
	}

	return ret;
}