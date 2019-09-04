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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct vfio_pci_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int VFIO_IRQ_SET_DATA_BOOL ; 
 int VFIO_IRQ_SET_DATA_EVENTFD ; 
 int VFIO_IRQ_SET_DATA_NONE ; 
 int /*<<< orphan*/  is_intx (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_pci_intx_mask (struct vfio_pci_device*) ; 

__attribute__((used)) static int vfio_pci_set_intx_mask(struct vfio_pci_device *vdev,
				  unsigned index, unsigned start,
				  unsigned count, uint32_t flags, void *data)
{
	if (!is_intx(vdev) || start != 0 || count != 1)
		return -EINVAL;

	if (flags & VFIO_IRQ_SET_DATA_NONE) {
		vfio_pci_intx_mask(vdev);
	} else if (flags & VFIO_IRQ_SET_DATA_BOOL) {
		uint8_t mask = *(uint8_t *)data;
		if (mask)
			vfio_pci_intx_mask(vdev);
	} else if (flags & VFIO_IRQ_SET_DATA_EVENTFD) {
		return -ENOTTY; /* XXX implement me */
	}

	return 0;
}