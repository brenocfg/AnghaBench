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
struct TYPE_9__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; TYPE_3__* regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct ehci_hcd {int big_endian_mmio; int big_endian_desc; int big_endian_capbase; TYPE_3__* caps; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  hc_capbase; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ GRUSBHC_HCIVERSION ; 
 scalar_t__ HC_VERSION (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int NO_IRQ ; 
 int PTR_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  ehci_grlib_hc_driver ; 
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_hcd_grlib_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct usb_hcd *hcd;
	struct ehci_hcd	*ehci = NULL;
	struct resource res;
	u32 hc_capbase;
	int irq;
	int rv;

	if (usb_disabled())
		return -ENODEV;

	dev_dbg(&op->dev, "initializing GRUSBHC EHCI USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	if (rv)
		return rv;

	/* usb_create_hcd requires dma_mask != NULL */
	op->dev.dma_mask = &op->dev.coherent_dma_mask;
	hcd = usb_create_hcd(&ehci_grlib_hc_driver, &op->dev,
			"GRUSBHC EHCI USB");
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

	ehci->caps = hcd->regs;

	/* determine endianness of this implementation */
	hc_capbase = ehci_readl(ehci, &ehci->caps->hc_capbase);
	if (HC_VERSION(ehci, hc_capbase) != GRUSBHC_HCIVERSION) {
		ehci->big_endian_mmio = 1;
		ehci->big_endian_desc = 1;
		ehci->big_endian_capbase = 1;
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