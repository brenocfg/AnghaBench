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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct amd_ntb_dev {int entry; int num; int db_count; int msix_vec_count; struct amd_ntb_dev* vec; struct amd_ntb_dev* msix; int /*<<< orphan*/  vector; struct amd_ntb_dev* ndev; int /*<<< orphan*/  db_valid_mask; int /*<<< orphan*/  db_mask; TYPE_1__ ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct amd_ntb_dev*) ; 
 void* kcalloc_node (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  ndev_irq_isr ; 
 int /*<<< orphan*/  ndev_vec_isr ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int pci_enable_msix_range (struct pci_dev*,struct amd_ntb_dev*,int,int) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct amd_ntb_dev*) ; 

__attribute__((used)) static int ndev_init_isr(struct amd_ntb_dev *ndev,
			 int msix_min, int msix_max)
{
	struct pci_dev *pdev;
	int rc, i, msix_count, node;

	pdev = ndev->ntb.pdev;

	node = dev_to_node(&pdev->dev);

	ndev->db_mask = ndev->db_valid_mask;

	/* Try to set up msix irq */
	ndev->vec = kcalloc_node(msix_max, sizeof(*ndev->vec),
				 GFP_KERNEL, node);
	if (!ndev->vec)
		goto err_msix_vec_alloc;

	ndev->msix = kcalloc_node(msix_max, sizeof(*ndev->msix),
				  GFP_KERNEL, node);
	if (!ndev->msix)
		goto err_msix_alloc;

	for (i = 0; i < msix_max; ++i)
		ndev->msix[i].entry = i;

	msix_count = pci_enable_msix_range(pdev, ndev->msix,
					   msix_min, msix_max);
	if (msix_count < 0)
		goto err_msix_enable;

	/* NOTE: Disable MSIX if msix count is less than 16 because of
	 * hardware limitation.
	 */
	if (msix_count < msix_min) {
		pci_disable_msix(pdev);
		goto err_msix_enable;
	}

	for (i = 0; i < msix_count; ++i) {
		ndev->vec[i].ndev = ndev;
		ndev->vec[i].num = i;
		rc = request_irq(ndev->msix[i].vector, ndev_vec_isr, 0,
				 "ndev_vec_isr", &ndev->vec[i]);
		if (rc)
			goto err_msix_request;
	}

	dev_dbg(&pdev->dev, "Using msix interrupts\n");
	ndev->db_count = msix_min;
	ndev->msix_vec_count = msix_max;
	return 0;

err_msix_request:
	while (i-- > 0)
		free_irq(ndev->msix[i].vector, &ndev->vec[i]);
	pci_disable_msix(pdev);
err_msix_enable:
	kfree(ndev->msix);
err_msix_alloc:
	kfree(ndev->vec);
err_msix_vec_alloc:
	ndev->msix = NULL;
	ndev->vec = NULL;

	/* Try to set up msi irq */
	rc = pci_enable_msi(pdev);
	if (rc)
		goto err_msi_enable;

	rc = request_irq(pdev->irq, ndev_irq_isr, 0,
			 "ndev_irq_isr", ndev);
	if (rc)
		goto err_msi_request;

	dev_dbg(&pdev->dev, "Using msi interrupts\n");
	ndev->db_count = 1;
	ndev->msix_vec_count = 1;
	return 0;

err_msi_request:
	pci_disable_msi(pdev);
err_msi_enable:

	/* Try to set up intx irq */
	pci_intx(pdev, 1);

	rc = request_irq(pdev->irq, ndev_irq_isr, IRQF_SHARED,
			 "ndev_irq_isr", ndev);
	if (rc)
		goto err_intx_request;

	dev_dbg(&pdev->dev, "Using intx interrupts\n");
	ndev->db_count = 1;
	ndev->msix_vec_count = 1;
	return 0;

err_intx_request:
	return rc;
}