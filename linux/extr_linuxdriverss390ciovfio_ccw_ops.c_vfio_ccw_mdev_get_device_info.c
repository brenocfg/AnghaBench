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
struct vfio_device_info {int flags; int /*<<< orphan*/  num_irqs; int /*<<< orphan*/  num_regions; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_CCW_NUM_IRQS ; 
 int /*<<< orphan*/  VFIO_CCW_NUM_REGIONS ; 
 int VFIO_DEVICE_FLAGS_CCW ; 
 int VFIO_DEVICE_FLAGS_RESET ; 

__attribute__((used)) static int vfio_ccw_mdev_get_device_info(struct vfio_device_info *info)
{
	info->flags = VFIO_DEVICE_FLAGS_CCW | VFIO_DEVICE_FLAGS_RESET;
	info->num_regions = VFIO_CCW_NUM_REGIONS;
	info->num_irqs = VFIO_CCW_NUM_IRQS;

	return 0;
}