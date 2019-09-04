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
struct vfio_platform_device {int /*<<< orphan*/  reset_module; scalar_t__ of_reset; } ;

/* Variables and functions */
 scalar_t__ VFIO_PLATFORM_IS_ACPI (struct vfio_platform_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfio_platform_put_reset(struct vfio_platform_device *vdev)
{
	if (VFIO_PLATFORM_IS_ACPI(vdev))
		return;

	if (vdev->of_reset)
		module_put(vdev->reset_module);
}