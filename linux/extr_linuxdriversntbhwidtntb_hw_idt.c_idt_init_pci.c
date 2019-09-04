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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct pci_dev* pdev; } ;
struct idt_ntb_dev {int /*<<< orphan*/  cfgspc; TYPE_1__ ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  NTB_NAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_get_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_cleanup_aer_uncorrect_error_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 int pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions_request_all (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 

__attribute__((used)) static int idt_init_pci(struct idt_ntb_dev *ndev)
{
	struct pci_dev *pdev = ndev->ntb.pdev;
	int ret;

	/* Initialize the bit mask of PCI/NTB DMA */
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (ret != 0) {
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (ret != 0) {
			dev_err(&pdev->dev, "Failed to set DMA bit mask\n");
			return ret;
		}
		dev_warn(&pdev->dev, "Cannot set DMA highmem bit mask\n");
	}
	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	if (ret != 0) {
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		if (ret != 0) {
			dev_err(&pdev->dev,
				"Failed to set consistent DMA bit mask\n");
			return ret;
		}
		dev_warn(&pdev->dev,
			"Cannot set consistent DMA highmem bit mask\n");
	}
	ret = dma_coerce_mask_and_coherent(&ndev->ntb.dev,
					   dma_get_mask(&pdev->dev));
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to set NTB device DMA bit mask\n");
		return ret;
	}

	/*
	 * Enable the device advanced error reporting. It's not critical to
	 * have AER disabled in the kernel.
	 */
	ret = pci_enable_pcie_error_reporting(pdev);
	if (ret != 0)
		dev_warn(&pdev->dev, "PCIe AER capability disabled\n");
	else /* Cleanup uncorrectable error status before getting to init */
		pci_cleanup_aer_uncorrect_error_status(pdev);

	/* First enable the PCI device */
	ret = pcim_enable_device(pdev);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to enable PCIe device\n");
		goto err_disable_aer;
	}

	/*
	 * Enable the bus mastering, which effectively enables MSI IRQs and
	 * Request TLPs translation
	 */
	pci_set_master(pdev);

	/* Request all BARs resources and map BAR0 only */
	ret = pcim_iomap_regions_request_all(pdev, 1, NTB_NAME);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request resources\n");
		goto err_clear_master;
	}

	/* Retrieve virtual address of BAR0 - PCI configuration space */
	ndev->cfgspc = pcim_iomap_table(pdev)[0];

	/* Put the IDT driver data pointer to the PCI-device private pointer */
	pci_set_drvdata(pdev, ndev);

	dev_dbg(&pdev->dev, "NT-function PCIe interface initialized");

	return 0;

err_clear_master:
	pci_clear_master(pdev);
err_disable_aer:
	(void)pci_disable_pcie_error_reporting(pdev);

	return ret;
}