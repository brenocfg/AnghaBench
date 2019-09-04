#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtio_pci_device {int msix_vectors; TYPE_1__* pci_dev; scalar_t__ intx_enabled; } ;
struct virtio_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

void vp_synchronize_vectors(struct virtio_device *vdev)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	int i;

	if (vp_dev->intx_enabled)
		synchronize_irq(vp_dev->pci_dev->irq);

	for (i = 0; i < vp_dev->msix_vectors; ++i)
		synchronize_irq(pci_irq_vector(vp_dev->pci_dev, i));
}