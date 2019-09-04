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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfio_pci_device {int /*<<< orphan*/  req_trigger; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int VFIO_PCI_REQ_IRQ_INDEX ; 
 int vfio_pci_set_ctx_trigger_single (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int vfio_pci_set_req_trigger(struct vfio_pci_device *vdev,
				    unsigned index, unsigned start,
				    unsigned count, uint32_t flags, void *data)
{
	if (index != VFIO_PCI_REQ_IRQ_INDEX || start != 0 || count > 1)
		return -EINVAL;

	return vfio_pci_set_ctx_trigger_single(&vdev->req_trigger,
					       count, flags, data);
}