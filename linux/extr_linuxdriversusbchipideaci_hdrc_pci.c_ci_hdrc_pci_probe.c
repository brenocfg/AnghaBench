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
struct resource {int /*<<< orphan*/  flags; scalar_t__ start; int /*<<< orphan*/  end; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct ci_hdrc_platform_data {int dummy; } ;
struct ci_hdrc_pci {int /*<<< orphan*/  ci; int /*<<< orphan*/  phy; } ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_hdrc_add_device (int /*<<< orphan*/ *,struct resource*,int,struct ci_hdrc_platform_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ci_hdrc_pci* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ci_hdrc_pci*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_phy_generic_register () ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_hdrc_pci_probe(struct pci_dev *pdev,
				       const struct pci_device_id *id)
{
	struct ci_hdrc_platform_data *platdata = (void *)id->driver_data;
	struct ci_hdrc_pci *ci;
	struct resource res[3];
	int retval = 0, nres = 2;

	if (!platdata) {
		dev_err(&pdev->dev, "device doesn't provide driver data\n");
		return -ENODEV;
	}

	ci = devm_kzalloc(&pdev->dev, sizeof(*ci), GFP_KERNEL);
	if (!ci)
		return -ENOMEM;

	retval = pcim_enable_device(pdev);
	if (retval)
		return retval;

	if (!pdev->irq) {
		dev_err(&pdev->dev, "No IRQ, check BIOS/PCI setup!");
		return -ENODEV;
	}

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	/* register a nop PHY */
	ci->phy = usb_phy_generic_register();
	if (IS_ERR(ci->phy))
		return PTR_ERR(ci->phy);

	memset(res, 0, sizeof(res));
	res[0].start	= pci_resource_start(pdev, 0);
	res[0].end	= pci_resource_end(pdev, 0);
	res[0].flags	= IORESOURCE_MEM;
	res[1].start	= pdev->irq;
	res[1].flags	= IORESOURCE_IRQ;

	ci->ci = ci_hdrc_add_device(&pdev->dev, res, nres, platdata);
	if (IS_ERR(ci->ci)) {
		dev_err(&pdev->dev, "ci_hdrc_add_device failed!\n");
		usb_phy_generic_unregister(ci->phy);
		return PTR_ERR(ci->ci);
	}

	pci_set_drvdata(pdev, ci);

	return 0;
}