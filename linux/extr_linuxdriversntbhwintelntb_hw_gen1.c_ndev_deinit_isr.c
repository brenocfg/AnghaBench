#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct intel_ntb_dev {int db_vec_count; struct intel_ntb_dev* vec; struct intel_ntb_dev* msix; int /*<<< orphan*/  vector; TYPE_3__* self_reg; scalar_t__ self_mmio; int /*<<< orphan*/  db_mask; TYPE_2__* reg; int /*<<< orphan*/  db_valid_mask; TYPE_1__ ntb; } ;
struct TYPE_6__ {scalar_t__ db_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* db_iowrite ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct intel_ntb_dev*) ; 
 int /*<<< orphan*/  kfree (struct intel_ntb_dev*) ; 
 scalar_t__ pci_dev_msi_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ndev_deinit_isr(struct intel_ntb_dev *ndev)
{
	struct pci_dev *pdev;
	int i;

	pdev = ndev->ntb.pdev;

	/* Mask all doorbell interrupts */
	ndev->db_mask = ndev->db_valid_mask;
	ndev->reg->db_iowrite(ndev->db_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_mask);

	if (ndev->msix) {
		i = ndev->db_vec_count;
		while (i--)
			free_irq(ndev->msix[i].vector, &ndev->vec[i]);
		pci_disable_msix(pdev);
		kfree(ndev->msix);
		kfree(ndev->vec);
	} else {
		free_irq(pdev->irq, ndev);
		if (pci_dev_msi_enabled(pdev))
			pci_disable_msi(pdev);
	}
}