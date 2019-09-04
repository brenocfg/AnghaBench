#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; struct clk* regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct spear_ehci {struct clk* clk; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hc_driver {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {struct clk* caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hc_driver ehci_spear_hc_driver ; 
 TYPE_2__* hcd_to_ehci (struct usb_hcd*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct spear_ehci* to_spear_ehci (struct usb_hcd*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int spear_ehci_hcd_drv_probe(struct platform_device *pdev)
{
	struct usb_hcd *hcd ;
	struct spear_ehci *sehci;
	struct resource *res;
	struct clk *usbh_clk;
	const struct hc_driver *driver = &ehci_spear_hc_driver;
	int irq, retval;

	if (usb_disabled())
		return -ENODEV;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		retval = irq;
		goto fail;
	}

	/*
	 * Right now device-tree probed devices don't get dma_mask set.
	 * Since shared usb code relies on it, set it here for now.
	 * Once we have dma capability bindings this can go away.
	 */
	retval = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (retval)
		goto fail;

	usbh_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(usbh_clk)) {
		dev_err(&pdev->dev, "Error getting interface clock\n");
		retval = PTR_ERR(usbh_clk);
		goto fail;
	}

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		retval = -ENOMEM;
		goto fail;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hcd->regs)) {
		retval = PTR_ERR(hcd->regs);
		goto err_put_hcd;
	}
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	sehci = to_spear_ehci(hcd);
	sehci->clk = usbh_clk;

	/* registers start at offset 0x0 */
	hcd_to_ehci(hcd)->caps = hcd->regs;

	clk_prepare_enable(sehci->clk);
	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (retval)
		goto err_stop_ehci;

	device_wakeup_enable(hcd->self.controller);
	return retval;

err_stop_ehci:
	clk_disable_unprepare(sehci->clk);
err_put_hcd:
	usb_put_hcd(hcd);
fail:
	dev_err(&pdev->dev, "init fail, %d\n", retval);

	return retval ;
}