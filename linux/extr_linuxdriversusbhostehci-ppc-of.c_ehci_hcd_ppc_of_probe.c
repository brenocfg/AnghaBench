#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  regs; int /*<<< orphan*/  rsrc_len; scalar_t__ rsrc_start; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct ehci_hcd {int has_amcc_usb23; int big_endian_mmio; int big_endian_desc; int /*<<< orphan*/  caps; int /*<<< orphan*/  ohci_hcctrl_reg; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NO_IRQ ; 
 int /*<<< orphan*/  OHCI_HCCTRL_LEN ; 
 scalar_t__ OHCI_HCCTRL_OFFSET ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,char*) ; 
 int /*<<< orphan*/  ehci_ppc_of_hc_driver ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int ppc44x_enable_bmt (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_hcd_ppc_of_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct usb_hcd *hcd;
	struct ehci_hcd	*ehci = NULL;
	struct resource res;
	int irq;
	int rv;

	struct device_node *np;

	if (usb_disabled())
		return -ENODEV;

	dev_dbg(&op->dev, "initializing PPC-OF USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	if (rv)
		return rv;

	hcd = usb_create_hcd(&ehci_ppc_of_hc_driver, &op->dev, "PPC-OF USB");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	irq = irq_of_parse_and_map(dn, 0);
	if (irq == NO_IRQ) {
		dev_err(&op->dev, "%s: irq_of_parse_and_map failed\n",
			__FILE__);
		rv = -EBUSY;
		goto err_irq;
	}

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	if (IS_ERR(hcd->regs)) {
		rv = PTR_ERR(hcd->regs);
		goto err_ioremap;
	}

	ehci = hcd_to_ehci(hcd);
	np = of_find_compatible_node(NULL, NULL, "ibm,usb-ohci-440epx");
	if (np != NULL) {
		/* claim we really affected by usb23 erratum */
		if (!of_address_to_resource(np, 0, &res))
			ehci->ohci_hcctrl_reg =
				devm_ioremap(&op->dev,
					     res.start + OHCI_HCCTRL_OFFSET,
					     OHCI_HCCTRL_LEN);
		else
			pr_debug("%s: no ohci offset in fdt\n", __FILE__);
		if (!ehci->ohci_hcctrl_reg) {
			pr_debug("%s: ioremap for ohci hcctrl failed\n", __FILE__);
		} else {
			ehci->has_amcc_usb23 = 1;
		}
	}

	if (of_get_property(dn, "big-endian", NULL)) {
		ehci->big_endian_mmio = 1;
		ehci->big_endian_desc = 1;
	}
	if (of_get_property(dn, "big-endian-regs", NULL))
		ehci->big_endian_mmio = 1;
	if (of_get_property(dn, "big-endian-desc", NULL))
		ehci->big_endian_desc = 1;

	ehci->caps = hcd->regs;

	if (of_device_is_compatible(dn, "ibm,usb-ehci-440epx")) {
		rv = ppc44x_enable_bmt(dn);
		ehci_dbg(ehci, "Break Memory Transfer (BMT) is %senabled!\n",
				rv ? "NOT ": "");
	}

	rv = usb_add_hcd(hcd, irq, 0);
	if (rv)
		goto err_ioremap;

	device_wakeup_enable(hcd->self.controller);
	return 0;

err_ioremap:
	irq_dispose_mapping(irq);
err_irq:
	usb_put_hcd(hcd);

	return rv;
}