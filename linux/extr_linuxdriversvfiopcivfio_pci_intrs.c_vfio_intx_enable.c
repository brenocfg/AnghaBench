#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfio_pci_irq_ctx {int dummy; } ;
struct vfio_pci_device {int num_ctx; int /*<<< orphan*/  irq_type; TYPE_2__* ctx; TYPE_1__* pdev; scalar_t__ pci_2_3; int /*<<< orphan*/  virq_disabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  masked; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VFIO_PCI_INTX_IRQ_INDEX ; 
 int /*<<< orphan*/  is_irq_none (struct vfio_pci_device*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_intx (TYPE_1__*,int) ; 

__attribute__((used)) static int vfio_intx_enable(struct vfio_pci_device *vdev)
{
	if (!is_irq_none(vdev))
		return -EINVAL;

	if (!vdev->pdev->irq)
		return -ENODEV;

	vdev->ctx = kzalloc(sizeof(struct vfio_pci_irq_ctx), GFP_KERNEL);
	if (!vdev->ctx)
		return -ENOMEM;

	vdev->num_ctx = 1;

	/*
	 * If the virtual interrupt is masked, restore it.  Devices
	 * supporting DisINTx can be masked at the hardware level
	 * here, non-PCI-2.3 devices will have to wait until the
	 * interrupt is enabled.
	 */
	vdev->ctx[0].masked = vdev->virq_disabled;
	if (vdev->pci_2_3)
		pci_intx(vdev->pdev, !vdev->ctx[0].masked);

	vdev->irq_type = VFIO_PCI_INTX_IRQ_INDEX;

	return 0;
}