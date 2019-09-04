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
struct usb_hcd {int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; int /*<<< orphan*/  regs; TYPE_1__ self; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct hc_driver {int dummy; } ;
struct ehci_hcd {int big_endian_mmio; int big_endian_desc; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  to_mspusb_device (struct platform_device*) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,int /*<<< orphan*/ *,char*) ; 
 int usb_hcd_msp_map_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

int usb_hcd_msp_probe(const struct hc_driver *driver,
			  struct platform_device *dev)
{
	int retval;
	struct usb_hcd *hcd;
	struct resource *res;
	struct ehci_hcd		*ehci ;

	hcd = usb_create_hcd(driver, &dev->dev, "pmcmsp");
	if (!hcd)
		return -ENOMEM;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		pr_debug("No IOMEM resource info for %s.\n", dev->name);
		retval = -ENOMEM;
		goto err1;
	}
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);
	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, dev->name)) {
		retval = -EBUSY;
		goto err1;
	}
	hcd->regs = ioremap_nocache(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		pr_debug("ioremap failed");
		retval = -ENOMEM;
		goto err2;
	}

	res = platform_get_resource(dev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		dev_err(&dev->dev, "No IRQ resource info for %s.\n", dev->name);
		retval = -ENOMEM;
		goto err3;
	}

	/* Map non-EHCI register spaces */
	retval = usb_hcd_msp_map_regs(to_mspusb_device(dev));
	if (retval != 0)
		goto err3;

	ehci = hcd_to_ehci(hcd);
	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;


	retval = usb_add_hcd(hcd, res->start, IRQF_SHARED);
	if (retval == 0) {
		device_wakeup_enable(hcd->self.controller);
		return 0;
	}

	usb_remove_hcd(hcd);
err3:
	iounmap(hcd->regs);
err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err1:
	usb_put_hcd(hcd);

	return retval;
}