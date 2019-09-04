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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bfad_s {int /*<<< orphan*/  bfad_flags; int /*<<< orphan*/  pcidev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pci_cleanup_aer_uncorrect_error_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 struct bfad_s* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 scalar_t__ pci_set_dma_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int restart_bfa (struct bfad_s*) ; 

__attribute__((used)) static pci_ers_result_t
bfad_pci_slot_reset(struct pci_dev *pdev)
{
	struct bfad_s *bfad = pci_get_drvdata(pdev);
	u8 byte;

	dev_printk(KERN_ERR, &pdev->dev,
		   "bfad_pci_slot_reset flags: 0x%x\n", bfad->bfad_flags);

	if (pci_enable_device(pdev)) {
		dev_printk(KERN_ERR, &pdev->dev, "Cannot re-enable "
			   "PCI device after reset.\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_restore_state(pdev);

	/*
	 * Read some byte (e.g. DMA max. payload size which can't
	 * be 0xff any time) to make sure - we did not hit another PCI error
	 * in the middle of recovery. If we did, then declare permanent failure.
	 */
	pci_read_config_byte(pdev, 0x68, &byte);
	if (byte == 0xff) {
		dev_printk(KERN_ERR, &pdev->dev,
			   "slot_reset failed ... got another PCI error !\n");
		goto out_disable_device;
	}

	pci_save_state(pdev);
	pci_set_master(pdev);

	if (pci_set_dma_mask(bfad->pcidev, DMA_BIT_MASK(64)) != 0)
		if (pci_set_dma_mask(bfad->pcidev, DMA_BIT_MASK(32)) != 0)
			goto out_disable_device;

	pci_cleanup_aer_uncorrect_error_status(pdev);

	if (restart_bfa(bfad) == -1)
		goto out_disable_device;

	pci_enable_pcie_error_reporting(pdev);
	dev_printk(KERN_WARNING, &pdev->dev,
		   "slot_reset completed  flags: 0x%x!\n", bfad->bfad_flags);

	return PCI_ERS_RESULT_RECOVERED;

out_disable_device:
	pci_disable_device(pdev);
	return PCI_ERS_RESULT_DISCONNECT;
}