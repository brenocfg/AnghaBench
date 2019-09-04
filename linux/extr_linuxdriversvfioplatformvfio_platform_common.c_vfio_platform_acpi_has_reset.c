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
struct vfio_platform_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool vfio_platform_acpi_has_reset(struct vfio_platform_device *vdev)
{
#ifdef CONFIG_ACPI
	struct device *dev = vdev->device;
	acpi_handle handle = ACPI_HANDLE(dev);

	return acpi_has_method(handle, "_RST");
#else
	return false;
#endif
}