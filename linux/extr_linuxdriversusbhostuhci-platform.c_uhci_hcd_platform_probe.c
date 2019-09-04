#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_2__ self; int /*<<< orphan*/  regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct uhci_hcd {int is_aspeed; int /*<<< orphan*/  clk; int /*<<< orphan*/  rh_numports; int /*<<< orphan*/  regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__* resource; TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int dma_coerce_mask_and_coherent (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct uhci_hcd* hcd_to_uhci (struct usb_hcd*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  uhci_platform_hc_driver ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int uhci_hcd_platform_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct usb_hcd *hcd;
	struct uhci_hcd	*uhci;
	struct resource *res;
	int ret;

	if (usb_disabled())
		return -ENODEV;

	/*
	 * Right now device-tree probed devices don't get dma_mask set.
	 * Since shared usb code relies on it, set it here for now.
	 * Once we have dma capability bindings this can go away.
	 */
	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	hcd = usb_create_hcd(&uhci_platform_hc_driver, &pdev->dev,
			pdev->name);
	if (!hcd)
		return -ENOMEM;

	uhci = hcd_to_uhci(hcd);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hcd->regs)) {
		ret = PTR_ERR(hcd->regs);
		goto err_rmr;
	}
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	uhci->regs = hcd->regs;

	/* Grab some things from the device-tree */
	if (np) {
		u32 num_ports;

		if (of_property_read_u32(np, "#ports", &num_ports) == 0) {
			uhci->rh_numports = num_ports;
			dev_info(&pdev->dev,
				"Detected %d ports from device-tree\n",
				num_ports);
		}
		if (of_device_is_compatible(np, "aspeed,ast2400-uhci") ||
		    of_device_is_compatible(np, "aspeed,ast2500-uhci")) {
			uhci->is_aspeed = 1;
			dev_info(&pdev->dev,
				 "Enabled Aspeed implementation workarounds\n");
		}
	}

	/* Get and enable clock if any specified */
	uhci->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(uhci->clk)) {
		ret = PTR_ERR(uhci->clk);
		goto err_rmr;
	}
	ret = clk_prepare_enable(uhci->clk);
	if (ret) {
		dev_err(&pdev->dev, "Error couldn't enable clock (%d)\n", ret);
		goto err_rmr;
	}

	ret = usb_add_hcd(hcd, pdev->resource[1].start, IRQF_SHARED);
	if (ret)
		goto err_clk;

	device_wakeup_enable(hcd->self.controller);
	return 0;

err_clk:
	clk_disable_unprepare(uhci->clk);
err_rmr:
	usb_put_hcd(hcd);

	return ret;
}