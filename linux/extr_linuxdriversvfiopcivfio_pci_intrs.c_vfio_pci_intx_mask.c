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
struct vfio_pci_device {int /*<<< orphan*/  irqlock; TYPE_1__* ctx; scalar_t__ pci_2_3; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int masked; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_intx (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void vfio_pci_intx_mask(struct vfio_pci_device *vdev)
{
	struct pci_dev *pdev = vdev->pdev;
	unsigned long flags;

	spin_lock_irqsave(&vdev->irqlock, flags);

	/*
	 * Masking can come from interrupt, ioctl, or config space
	 * via INTx disable.  The latter means this can get called
	 * even when not using intx delivery.  In this case, just
	 * try to have the physical bit follow the virtual bit.
	 */
	if (unlikely(!is_intx(vdev))) {
		if (vdev->pci_2_3)
			pci_intx(pdev, 0);
	} else if (!vdev->ctx[0].masked) {
		/*
		 * Can't use check_and_mask here because we always want to
		 * mask, not just when something is pending.
		 */
		if (vdev->pci_2_3)
			pci_intx(pdev, 0);
		else
			disable_irq_nosync(pdev->irq);

		vdev->ctx[0].masked = true;
	}

	spin_unlock_irqrestore(&vdev->irqlock, flags);
}