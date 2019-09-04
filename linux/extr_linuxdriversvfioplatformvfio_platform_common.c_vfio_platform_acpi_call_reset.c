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
 int ENOENT ; 

__attribute__((used)) static int vfio_platform_acpi_call_reset(struct vfio_platform_device *vdev,
				  const char **extra_dbg)
{
#ifdef CONFIG_ACPI
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct device *dev = vdev->device;
	acpi_handle handle = ACPI_HANDLE(dev);
	acpi_status acpi_ret;

	acpi_ret = acpi_evaluate_object(handle, "_RST", NULL, &buffer);
	if (ACPI_FAILURE(acpi_ret)) {
		if (extra_dbg)
			*extra_dbg = acpi_format_exception(acpi_ret);
		return -EINVAL;
	}

	return 0;
#else
	return -ENOENT;
#endif
}