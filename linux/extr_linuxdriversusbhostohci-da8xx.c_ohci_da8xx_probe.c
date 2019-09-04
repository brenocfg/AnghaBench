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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; int /*<<< orphan*/ * regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct da8xx_ohci_hcd {int /*<<< orphan*/ * vbus_reg; int /*<<< orphan*/ * usb11_phy; int /*<<< orphan*/ * usb11_clk; struct usb_hcd* hcd; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/ * devm_phy_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ohci_da8xx_hc_driver ; 
 int ohci_da8xx_register_notify (struct usb_hcd*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct da8xx_ohci_hcd* to_da8xx_ohci (struct usb_hcd*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_da8xx_probe(struct platform_device *pdev)
{
	struct da8xx_ohci_hcd *da8xx_ohci;
	struct usb_hcd	*hcd;
	struct resource *mem;
	int error, irq;
	hcd = usb_create_hcd(&ohci_da8xx_hc_driver, &pdev->dev,
				dev_name(&pdev->dev));
	if (!hcd)
		return -ENOMEM;

	da8xx_ohci = to_da8xx_ohci(hcd);
	da8xx_ohci->hcd = hcd;

	da8xx_ohci->usb11_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(da8xx_ohci->usb11_clk)) {
		error = PTR_ERR(da8xx_ohci->usb11_clk);
		if (error != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get clock.\n");
		goto err;
	}

	da8xx_ohci->usb11_phy = devm_phy_get(&pdev->dev, "usb-phy");
	if (IS_ERR(da8xx_ohci->usb11_phy)) {
		error = PTR_ERR(da8xx_ohci->usb11_phy);
		if (error != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get phy.\n");
		goto err;
	}

	da8xx_ohci->vbus_reg = devm_regulator_get_optional(&pdev->dev, "vbus");
	if (IS_ERR(da8xx_ohci->vbus_reg)) {
		error = PTR_ERR(da8xx_ohci->vbus_reg);
		if (error == -ENODEV) {
			da8xx_ohci->vbus_reg = NULL;
		} else if (error == -EPROBE_DEFER) {
			goto err;
		} else {
			dev_err(&pdev->dev, "Failed to get regulator\n");
			goto err;
		}
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(hcd->regs)) {
		error = PTR_ERR(hcd->regs);
		goto err;
	}
	hcd->rsrc_start = mem->start;
	hcd->rsrc_len = resource_size(mem);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		error = -ENODEV;
		goto err;
	}

	error = usb_add_hcd(hcd, irq, 0);
	if (error)
		goto err;

	device_wakeup_enable(hcd->self.controller);

	error = ohci_da8xx_register_notify(hcd);
	if (error)
		goto err_remove_hcd;

	return 0;

err_remove_hcd:
	usb_remove_hcd(hcd);
err:
	usb_put_hcd(hcd);
	return error;
}