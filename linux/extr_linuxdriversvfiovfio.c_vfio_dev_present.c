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
struct vfio_group {int dummy; } ;
struct vfio_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfio_device_put (struct vfio_device*) ; 
 struct vfio_device* vfio_group_get_device (struct vfio_group*,struct device*) ; 

__attribute__((used)) static bool vfio_dev_present(struct vfio_group *group, struct device *dev)
{
	struct vfio_device *device;

	device = vfio_group_get_device(group, dev);
	if (!device)
		return false;

	vfio_device_put(device);
	return true;
}