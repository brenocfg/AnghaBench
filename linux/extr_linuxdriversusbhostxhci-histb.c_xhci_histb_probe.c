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
struct xhci_hcd_histb {struct usb_hcd* hcd; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  soft_reset; struct device* dev; } ;
struct xhci_hcd {int imod_interval; struct usb_hcd* shared_hcd; int /*<<< orphan*/  hcc_params; int /*<<< orphan*/  quirks; struct usb_hcd* main_hcd; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int can_do_streams; TYPE_1__ self; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; int /*<<< orphan*/  regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hc_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCC_MAX_PSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_HW_LPM_DISABLE ; 
 int /*<<< orphan*/  XHCI_LPM_SUPPORT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct xhci_hcd_histb*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (struct device*) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct xhci_hcd_histb* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,struct device*,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_shared_hcd (struct hc_driver const*,struct device*,int /*<<< orphan*/ ,struct usb_hcd*) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 
 int xhci_histb_clks_get (struct xhci_hcd_histb*) ; 
 struct hc_driver xhci_histb_hc_driver ; 
 int /*<<< orphan*/  xhci_histb_host_disable (struct xhci_hcd_histb*) ; 
 int xhci_histb_host_enable (struct xhci_hcd_histb*) ; 

__attribute__((used)) static int xhci_histb_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct xhci_hcd_histb *histb;
	const struct hc_driver *driver;
	struct usb_hcd *hcd;
	struct xhci_hcd *xhci;
	struct resource *res;
	int irq;
	int ret = -ENODEV;

	if (usb_disabled())
		return -ENODEV;

	driver = &xhci_histb_hc_driver;
	histb = devm_kzalloc(dev, sizeof(*histb), GFP_KERNEL);
	if (!histb)
		return -ENOMEM;

	histb->dev = dev;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	histb->ctrl = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(histb->ctrl))
		return PTR_ERR(histb->ctrl);

	ret = xhci_histb_clks_get(histb);
	if (ret)
		return ret;

	histb->soft_reset = devm_reset_control_get(dev, "soft");
	if (IS_ERR(histb->soft_reset)) {
		dev_err(dev, "failed to get soft reset\n");
		return PTR_ERR(histb->soft_reset);
	}

	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);
	device_enable_async_suspend(dev);

	/* Initialize dma_mask and coherent_dma_mask to 32-bits */
	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	hcd = usb_create_hcd(driver, dev, dev_name(dev));
	if (!hcd) {
		ret = -ENOMEM;
		goto disable_pm;
	}

	hcd->regs = histb->ctrl;
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	histb->hcd = hcd;
	dev_set_drvdata(hcd->self.controller, histb);

	ret = xhci_histb_host_enable(histb);
	if (ret)
		goto put_hcd;

	xhci = hcd_to_xhci(hcd);

	device_wakeup_enable(hcd->self.controller);

	xhci->main_hcd = hcd;
	xhci->shared_hcd = usb_create_shared_hcd(driver, dev, dev_name(dev),
						 hcd);
	if (!xhci->shared_hcd) {
		ret = -ENOMEM;
		goto disable_host;
	}

	if (device_property_read_bool(dev, "usb2-lpm-disable"))
		xhci->quirks |= XHCI_HW_LPM_DISABLE;

	if (device_property_read_bool(dev, "usb3-lpm-capable"))
		xhci->quirks |= XHCI_LPM_SUPPORT;

	/* imod_interval is the interrupt moderation value in nanoseconds. */
	xhci->imod_interval = 40000;
	device_property_read_u32(dev, "imod-interval-ns",
				 &xhci->imod_interval);

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (ret)
		goto put_usb3_hcd;

	if (HCC_MAX_PSA(xhci->hcc_params) >= 4)
		xhci->shared_hcd->can_do_streams = 1;

	ret = usb_add_hcd(xhci->shared_hcd, irq, IRQF_SHARED);
	if (ret)
		goto dealloc_usb2_hcd;

	device_enable_async_suspend(dev);
	pm_runtime_put_noidle(dev);

	/*
	 * Prevent runtime pm from being on as default, users should enable
	 * runtime pm using power/control in sysfs.
	 */
	pm_runtime_forbid(dev);

	return 0;

dealloc_usb2_hcd:
	usb_remove_hcd(hcd);
put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);
disable_host:
	xhci_histb_host_disable(histb);
put_hcd:
	usb_put_hcd(hcd);
disable_pm:
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);

	return ret;
}