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
struct vfio_irq_info {int index; int flags; int count; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int VFIO_IRQ_INFO_AUTOMASKED ; 
 int VFIO_IRQ_INFO_EVENTFD ; 
 int VFIO_IRQ_INFO_MASKABLE ; 
 int VFIO_IRQ_INFO_NORESIZE ; 
#define  VFIO_PCI_INTX_IRQ_INDEX 130 
#define  VFIO_PCI_MSI_IRQ_INDEX 129 
#define  VFIO_PCI_REQ_IRQ_INDEX 128 

int mtty_get_irq_info(struct mdev_device *mdev, struct vfio_irq_info *irq_info)
{
	switch (irq_info->index) {
	case VFIO_PCI_INTX_IRQ_INDEX:
	case VFIO_PCI_MSI_IRQ_INDEX:
	case VFIO_PCI_REQ_IRQ_INDEX:
		break;

	default:
		return -EINVAL;
	}

	irq_info->flags = VFIO_IRQ_INFO_EVENTFD;
	irq_info->count = 1;

	if (irq_info->index == VFIO_PCI_INTX_IRQ_INDEX)
		irq_info->flags |= (VFIO_IRQ_INFO_MASKABLE |
				VFIO_IRQ_INFO_AUTOMASKED);
	else
		irq_info->flags |= VFIO_IRQ_INFO_NORESIZE;

	return 0;
}