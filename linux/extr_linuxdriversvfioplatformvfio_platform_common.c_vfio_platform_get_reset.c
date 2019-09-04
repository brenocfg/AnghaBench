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
struct vfio_platform_device {void* of_reset; int /*<<< orphan*/  reset_module; int /*<<< orphan*/  compat; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ VFIO_PLATFORM_IS_ACPI (struct vfio_platform_device*) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vfio_platform_acpi_has_reset (struct vfio_platform_device*) ; 
 void* vfio_platform_lookup_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_platform_get_reset(struct vfio_platform_device *vdev)
{
	if (VFIO_PLATFORM_IS_ACPI(vdev))
		return vfio_platform_acpi_has_reset(vdev) ? 0 : -ENOENT;

	vdev->of_reset = vfio_platform_lookup_reset(vdev->compat,
						    &vdev->reset_module);
	if (!vdev->of_reset) {
		request_module("vfio-reset:%s", vdev->compat);
		vdev->of_reset = vfio_platform_lookup_reset(vdev->compat,
							&vdev->reset_module);
	}

	return vdev->of_reset ? 0 : -ENOENT;
}