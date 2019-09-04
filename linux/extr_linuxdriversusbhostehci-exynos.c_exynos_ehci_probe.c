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
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct exynos_ehci_hcd {int /*<<< orphan*/  clk; } ;
struct ehci_hcd {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  EHCI_INSNREG00 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EHCI_INSNREG00_ENABLE_DMA_BURST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int exynos_ehci_get_phy (int /*<<< orphan*/ *,struct exynos_ehci_hcd*) ; 
 int /*<<< orphan*/  exynos_ehci_hc_driver ; 
 int /*<<< orphan*/  exynos_ehci_phy_disable (int /*<<< orphan*/ *) ; 
 int exynos_ehci_phy_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_setup_vbus_gpio (int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usb_hcd*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct exynos_ehci_hcd* to_exynos_ehci (struct usb_hcd*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_ehci_probe(struct platform_device *pdev)
{
	struct exynos_ehci_hcd *exynos_ehci;
	struct usb_hcd *hcd;
	struct ehci_hcd *ehci;
	struct resource *res;
	int irq;
	int err;

	/*
	 * Right now device-tree probed devices don't get dma_mask set.
	 * Since shared usb code relies on it, set it here for now.
	 * Once we move to full device tree support this will vanish off.
	 */
	err = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (err)
		return err;

	exynos_setup_vbus_gpio(&pdev->dev);

	hcd = usb_create_hcd(&exynos_ehci_hc_driver,
			     &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		dev_err(&pdev->dev, "Unable to create HCD\n");
		return -ENOMEM;
	}
	exynos_ehci = to_exynos_ehci(hcd);

	err = exynos_ehci_get_phy(&pdev->dev, exynos_ehci);
	if (err)
		goto fail_clk;

	exynos_ehci->clk = devm_clk_get(&pdev->dev, "usbhost");

	if (IS_ERR(exynos_ehci->clk)) {
		dev_err(&pdev->dev, "Failed to get usbhost clock\n");
		err = PTR_ERR(exynos_ehci->clk);
		goto fail_clk;
	}

	err = clk_prepare_enable(exynos_ehci->clk);
	if (err)
		goto fail_clk;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hcd->regs)) {
		err = PTR_ERR(hcd->regs);
		goto fail_io;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	irq = platform_get_irq(pdev, 0);
	if (!irq) {
		dev_err(&pdev->dev, "Failed to get IRQ\n");
		err = -ENODEV;
		goto fail_io;
	}

	err = exynos_ehci_phy_enable(&pdev->dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to enable USB phy\n");
		goto fail_io;
	}

	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->regs;

	/* DMA burst Enable */
	writel(EHCI_INSNREG00_ENABLE_DMA_BURST, EHCI_INSNREG00(hcd->regs));

	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (err) {
		dev_err(&pdev->dev, "Failed to add USB HCD\n");
		goto fail_add_hcd;
	}
	device_wakeup_enable(hcd->self.controller);

	platform_set_drvdata(pdev, hcd);

	return 0;

fail_add_hcd:
	exynos_ehci_phy_disable(&pdev->dev);
fail_io:
	clk_disable_unprepare(exynos_ehci->clk);
fail_clk:
	usb_put_hcd(hcd);
	return err;
}