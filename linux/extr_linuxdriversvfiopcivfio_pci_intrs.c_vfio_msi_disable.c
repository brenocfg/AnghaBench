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
struct vfio_pci_device {int num_ctx; TYPE_1__* ctx; int /*<<< orphan*/  irq_type; scalar_t__ nointx; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  unmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_PCI_NUM_IRQS ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_msi_set_block (struct vfio_pci_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfio_virqfd_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_msi_disable(struct vfio_pci_device *vdev, bool msix)
{
	struct pci_dev *pdev = vdev->pdev;
	int i;

	for (i = 0; i < vdev->num_ctx; i++) {
		vfio_virqfd_disable(&vdev->ctx[i].unmask);
		vfio_virqfd_disable(&vdev->ctx[i].mask);
	}

	vfio_msi_set_block(vdev, 0, vdev->num_ctx, NULL, msix);

	pci_free_irq_vectors(pdev);

	/*
	 * Both disable paths above use pci_intx_for_msi() to clear DisINTx
	 * via their shutdown paths.  Restore for NoINTx devices.
	 */
	if (vdev->nointx)
		pci_intx(pdev, 0);

	vdev->irq_type = VFIO_PCI_NUM_IRQS;
	vdev->num_ctx = 0;
	kfree(vdev->ctx);
}