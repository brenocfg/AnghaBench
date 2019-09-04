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
struct vfio_device_info {int /*<<< orphan*/  num_irqs; int /*<<< orphan*/  num_regions; int /*<<< orphan*/  flags; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_DEVICE_FLAGS_PCI ; 
 int /*<<< orphan*/  VFIO_PCI_NUM_IRQS ; 
 int /*<<< orphan*/  VFIO_PCI_NUM_REGIONS ; 

__attribute__((used)) static int mbochs_get_device_info(struct mdev_device *mdev,
				  struct vfio_device_info *dev_info)
{
	dev_info->flags = VFIO_DEVICE_FLAGS_PCI;
	dev_info->num_regions = VFIO_PCI_NUM_REGIONS;
	dev_info->num_irqs = VFIO_PCI_NUM_IRQS;
	return 0;
}