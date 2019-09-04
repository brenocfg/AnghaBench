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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct intel_scu_ipc_pdata_t {int /*<<< orphan*/  i2c_len; int /*<<< orphan*/  i2c_base; int /*<<< orphan*/  irq_mode; } ;
struct intel_scu_ipc_dev {int /*<<< orphan*/ * dev; int /*<<< orphan*/  i2c_base; int /*<<< orphan*/  ipc_base; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  irq_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct intel_scu_ipc_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_scu_devices_create () ; 
 int /*<<< orphan*/  ioc ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_scu_ipc_dev ipcdev ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct intel_scu_ipc_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 

__attribute__((used)) static int ipc_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int err;
	struct intel_scu_ipc_dev *scu = &ipcdev;
	struct intel_scu_ipc_pdata_t *pdata;

	if (scu->dev)		/* We support only one SCU */
		return -EBUSY;

	pdata = (struct intel_scu_ipc_pdata_t *)id->driver_data;
	if (!pdata)
		return -ENODEV;

	scu->irq_mode = pdata->irq_mode;

	err = pcim_enable_device(pdev);
	if (err)
		return err;

	err = pcim_iomap_regions(pdev, 1 << 0, pci_name(pdev));
	if (err)
		return err;

	init_completion(&scu->cmd_complete);

	scu->ipc_base = pcim_iomap_table(pdev)[0];

	scu->i2c_base = ioremap_nocache(pdata->i2c_base, pdata->i2c_len);
	if (!scu->i2c_base)
		return -ENOMEM;

	err = devm_request_irq(&pdev->dev, pdev->irq, ioc, 0, "intel_scu_ipc",
			       scu);
	if (err)
		return err;

	/* Assign device at last */
	scu->dev = &pdev->dev;

	intel_scu_devices_create();

	pci_set_drvdata(pdev, scu);
	return 0;
}