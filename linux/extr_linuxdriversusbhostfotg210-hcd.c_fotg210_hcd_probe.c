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
struct usb_hcd {int has_tt; int rsrc_start; TYPE_2__ self; int /*<<< orphan*/  regs; int /*<<< orphan*/  rsrc_len; } ;
struct resource {int start; } ;
struct TYPE_3__ {int /*<<< orphan*/  power_state; } ;
struct device {TYPE_1__ power; } ;
struct platform_device {struct device dev; } ;
struct fotg210_hcd {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMSG_ON ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  fotg210_fotg210_hc_driver ; 
 int /*<<< orphan*/  fotg210_init (struct fotg210_hcd*) ; 
 int fotg210_setup (struct usb_hcd*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int fotg210_hcd_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct usb_hcd *hcd;
	struct resource *res;
	int irq;
	int retval = -ENODEV;
	struct fotg210_hcd *fotg210;

	if (usb_disabled())
		return -ENODEV;

	pdev->dev.power.power_state = PMSG_ON;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(dev, "Found HC with no IRQ. Check %s setup!\n",
				dev_name(dev));
		return -ENODEV;
	}

	irq = res->start;

	hcd = usb_create_hcd(&fotg210_fotg210_hc_driver, dev,
			dev_name(dev));
	if (!hcd) {
		dev_err(dev, "failed to create hcd with err %d\n", retval);
		retval = -ENOMEM;
		goto fail_create_hcd;
	}

	hcd->has_tt = 1;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hcd->regs)) {
		retval = PTR_ERR(hcd->regs);
		goto failed;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	fotg210 = hcd_to_fotg210(hcd);

	fotg210->caps = hcd->regs;

	retval = fotg210_setup(hcd);
	if (retval)
		goto failed;

	fotg210_init(fotg210);

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (retval) {
		dev_err(dev, "failed to add hcd with err %d\n", retval);
		goto failed;
	}
	device_wakeup_enable(hcd->self.controller);

	return retval;

failed:
	usb_put_hcd(hcd);
fail_create_hcd:
	dev_err(dev, "init %s fail, %d\n", dev_name(dev), retval);
	return retval;
}