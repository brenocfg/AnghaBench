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
struct vfio_pci_device {int /*<<< orphan*/  irqlock; TYPE_1__* ctx; int /*<<< orphan*/  pci_2_3; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct eventfd_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ masked; int /*<<< orphan*/  name; struct eventfd_ctx* trigger; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 int PTR_ERR (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int) ; 
 int /*<<< orphan*/  eventfd_ctx_put (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vfio_pci_device*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct vfio_pci_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfio_intx_handler ; 

__attribute__((used)) static int vfio_intx_set_signal(struct vfio_pci_device *vdev, int fd)
{
	struct pci_dev *pdev = vdev->pdev;
	unsigned long irqflags = IRQF_SHARED;
	struct eventfd_ctx *trigger;
	unsigned long flags;
	int ret;

	if (vdev->ctx[0].trigger) {
		free_irq(pdev->irq, vdev);
		kfree(vdev->ctx[0].name);
		eventfd_ctx_put(vdev->ctx[0].trigger);
		vdev->ctx[0].trigger = NULL;
	}

	if (fd < 0) /* Disable only */
		return 0;

	vdev->ctx[0].name = kasprintf(GFP_KERNEL, "vfio-intx(%s)",
				      pci_name(pdev));
	if (!vdev->ctx[0].name)
		return -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	if (IS_ERR(trigger)) {
		kfree(vdev->ctx[0].name);
		return PTR_ERR(trigger);
	}

	vdev->ctx[0].trigger = trigger;

	if (!vdev->pci_2_3)
		irqflags = 0;

	ret = request_irq(pdev->irq, vfio_intx_handler,
			  irqflags, vdev->ctx[0].name, vdev);
	if (ret) {
		vdev->ctx[0].trigger = NULL;
		kfree(vdev->ctx[0].name);
		eventfd_ctx_put(trigger);
		return ret;
	}

	/*
	 * INTx disable will stick across the new irq setup,
	 * disable_irq won't.
	 */
	spin_lock_irqsave(&vdev->irqlock, flags);
	if (!vdev->pci_2_3 && vdev->ctx[0].masked)
		disable_irq_nosync(pdev->irq);
	spin_unlock_irqrestore(&vdev->irqlock, flags);

	return 0;
}