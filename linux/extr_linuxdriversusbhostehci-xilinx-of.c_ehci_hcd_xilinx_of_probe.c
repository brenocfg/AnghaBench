#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int has_tt; TYPE_1__ self; scalar_t__ regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct ehci_hcd {int big_endian_mmio; int big_endian_desc; scalar_t__ caps; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_xilinx_of_hc_driver ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_hcd_xilinx_of_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct usb_hcd *hcd;
	struct ehci_hcd	*ehci;
	struct resource res;
	int irq;
	int rv;
	int *value;

	if (usb_disabled())
		return -ENODEV;

	dev_dbg(&op->dev, "initializing XILINX-OF USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	if (rv)
		return rv;

	hcd = usb_create_hcd(&ehci_xilinx_of_hc_driver, &op->dev,
				"XILINX-OF USB");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	irq = irq_of_parse_and_map(dn, 0);
	if (!irq) {
		dev_err(&op->dev, "%s: irq_of_parse_and_map failed\n",
			__FILE__);
		rv = -EBUSY;
		goto err_irq;
	}

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	if (IS_ERR(hcd->regs)) {
		rv = PTR_ERR(hcd->regs);
		goto err_irq;
	}

	ehci = hcd_to_ehci(hcd);

	/* This core always has big-endian register interface and uses
	 * big-endian memory descriptors.
	 */
	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;

	/* Check whether the FS support option is selected in the hardware.
	 */
	value = (int *)of_get_property(dn, "xlnx,support-usb-fs", NULL);
	if (value && (*value == 1)) {
		ehci_dbg(ehci, "USB host controller supports FS devices\n");
		hcd->has_tt = 1;
	} else {
		ehci_dbg(ehci,
			"USB host controller is HS only\n");
		hcd->has_tt = 0;
	}

	/* Debug registers are at the first 0x100 region
	 */
	ehci->caps = hcd->regs + 0x100;

	rv = usb_add_hcd(hcd, irq, 0);
	if (rv == 0) {
		device_wakeup_enable(hcd->self.controller);
		return 0;
	}

err_irq:
	usb_put_hcd(hcd);

	return rv;
}