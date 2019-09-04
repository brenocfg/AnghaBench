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
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {scalar_t__ rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/  regs; TYPE_2__ self; } ;
struct platform_device {int num_resources; int /*<<< orphan*/  dev; TYPE_1__* resource; } ;
struct TYPE_3__ {scalar_t__ flags; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ IORESOURCE_IRQ ; 
 scalar_t__ IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_omap15xx () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_name ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_omap_hc_driver ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dc_ck ; 
 int /*<<< orphan*/  usb_host_ck ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_omap_probe(struct platform_device *pdev)
{
	int retval, irq;
	struct usb_hcd *hcd = 0;

	if (pdev->num_resources != 2) {
		dev_err(&pdev->dev, "invalid num_resources: %i\n",
		       pdev->num_resources);
		return -ENODEV;
	}

	if (pdev->resource[0].flags != IORESOURCE_MEM
			|| pdev->resource[1].flags != IORESOURCE_IRQ) {
		dev_err(&pdev->dev, "invalid resource type\n");
		return -ENODEV;
	}

	usb_host_ck = clk_get(&pdev->dev, "usb_hhc_ck");
	if (IS_ERR(usb_host_ck))
		return PTR_ERR(usb_host_ck);

	if (!cpu_is_omap15xx())
		usb_dc_ck = clk_get(&pdev->dev, "usb_dc_ck");
	else
		usb_dc_ck = clk_get(&pdev->dev, "lb_ck");

	if (IS_ERR(usb_dc_ck)) {
		clk_put(usb_host_ck);
		return PTR_ERR(usb_dc_ck);
	}


	hcd = usb_create_hcd(&ohci_omap_hc_driver, &pdev->dev,
			dev_name(&pdev->dev));
	if (!hcd) {
		retval = -ENOMEM;
		goto err0;
	}
	hcd->rsrc_start = pdev->resource[0].start;
	hcd->rsrc_len = pdev->resource[0].end - pdev->resource[0].start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		dev_dbg(&pdev->dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err1;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		dev_err(&pdev->dev, "can't ioremap OHCI HCD\n");
		retval = -ENOMEM;
		goto err2;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		retval = -ENXIO;
		goto err3;
	}
	retval = usb_add_hcd(hcd, irq, 0);
	if (retval)
		goto err3;

	device_wakeup_enable(hcd->self.controller);
	return 0;
err3:
	iounmap(hcd->regs);
err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err1:
	usb_put_hcd(hcd);
err0:
	clk_put(usb_dc_ck);
	clk_put(usb_host_ck);
	return retval;
}