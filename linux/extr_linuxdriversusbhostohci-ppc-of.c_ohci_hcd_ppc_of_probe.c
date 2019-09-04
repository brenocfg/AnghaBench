#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct ohci_hcd {int flags; TYPE_2__* regs; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NO_IRQ ; 
 int OHCI_QUIRK_BE_DESC ; 
 int OHCI_QUIRK_BE_MMIO ; 
 int OHCI_QUIRK_FRAME_NO ; 
 int OHCI_USB_SUSPEND ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int /*<<< orphan*/  hcd_name ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ohci_hcd_init (struct ohci_hcd*) ; 
 int /*<<< orphan*/  ohci_ppc_of_hc_driver ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int readl_be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  writel_be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ohci_hcd_ppc_of_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct usb_hcd *hcd;
	struct ohci_hcd	*ohci;
	struct resource res;
	int irq;

	int rv;
	int is_bigendian;
	struct device_node *np;

	if (usb_disabled())
		return -ENODEV;

	is_bigendian =
		of_device_is_compatible(dn, "ohci-bigendian") ||
		of_device_is_compatible(dn, "ohci-be");

	dev_dbg(&op->dev, "initializing PPC-OF USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	if (rv)
		return rv;

	hcd = usb_create_hcd(&ohci_ppc_of_hc_driver, &op->dev, "PPC-OF USB");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	if (IS_ERR(hcd->regs)) {
		rv = PTR_ERR(hcd->regs);
		goto err_rmr;
	}

	irq = irq_of_parse_and_map(dn, 0);
	if (irq == NO_IRQ) {
		dev_err(&op->dev, "%s: irq_of_parse_and_map failed\n",
			__FILE__);
		rv = -EBUSY;
		goto err_rmr;
	}

	ohci = hcd_to_ohci(hcd);
	if (is_bigendian) {
		ohci->flags |= OHCI_QUIRK_BE_MMIO | OHCI_QUIRK_BE_DESC;
		if (of_device_is_compatible(dn, "fsl,mpc5200-ohci"))
			ohci->flags |= OHCI_QUIRK_FRAME_NO;
		if (of_device_is_compatible(dn, "mpc5200-ohci"))
			ohci->flags |= OHCI_QUIRK_FRAME_NO;
	}

	ohci_hcd_init(ohci);

	rv = usb_add_hcd(hcd, irq, 0);
	if (rv == 0) {
		device_wakeup_enable(hcd->self.controller);
		return 0;
	}

	/* by now, 440epx is known to show usb_23 erratum */
	np = of_find_compatible_node(NULL, NULL, "ibm,usb-ehci-440epx");

	/* Work around - At this point ohci_run has executed, the
	* controller is running, everything, the root ports, etc., is
	* set up.  If the ehci driver is loaded, put the ohci core in
	* the suspended state.  The ehci driver will bring it out of
	* suspended state when / if a non-high speed USB device is
	* attached to the USB Host port.  If the ehci driver is not
	* loaded, do nothing. request_mem_region is used to test if
	* the ehci driver is loaded.
	*/
	if (np !=  NULL) {
		if (!of_address_to_resource(np, 0, &res)) {
			if (!request_mem_region(res.start, 0x4, hcd_name)) {
				writel_be((readl_be(&ohci->regs->control) |
					OHCI_USB_SUSPEND), &ohci->regs->control);
					(void) readl_be(&ohci->regs->control);
			} else
				release_mem_region(res.start, 0x4);
		} else
			pr_debug("%s: cannot get ehci offset from fdt\n", __FILE__);
	}

	irq_dispose_mapping(irq);
err_rmr:
 	usb_put_hcd(hcd);

	return rv;
}