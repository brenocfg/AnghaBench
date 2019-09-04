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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct intel_pmc_ipc_dev {int /*<<< orphan*/ * dev; int /*<<< orphan*/  ipc_base; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  gcr_lock; int /*<<< orphan*/  irq_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IPC_TRIGGER_MODE_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct intel_pmc_ipc_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioc ; 
 struct intel_pmc_ipc_dev ipcdev ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct intel_pmc_ipc_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipc_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct intel_pmc_ipc_dev *pmc = &ipcdev;
	int ret;

	/* Only one PMC is supported */
	if (pmc->dev)
		return -EBUSY;

	pmc->irq_mode = IPC_TRIGGER_MODE_IRQ;

	spin_lock_init(&ipcdev.gcr_lock);

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	ret = pcim_iomap_regions(pdev, 1 << 0, pci_name(pdev));
	if (ret)
		return ret;

	init_completion(&pmc->cmd_complete);

	pmc->ipc_base = pcim_iomap_table(pdev)[0];

	ret = devm_request_irq(&pdev->dev, pdev->irq, ioc, 0, "intel_pmc_ipc",
				pmc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq\n");
		return ret;
	}

	pmc->dev = &pdev->dev;

	pci_set_drvdata(pdev, pmc);

	return 0;
}