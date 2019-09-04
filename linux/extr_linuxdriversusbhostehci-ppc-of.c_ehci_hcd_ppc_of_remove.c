#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  irq; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ehci_hcd {scalar_t__ has_amcc_usb23; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hcd_name ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ohci_hcfs (struct ehci_hcd*,int) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_hcd_ppc_of_remove(struct platform_device *op)
{
	struct usb_hcd *hcd = platform_get_drvdata(op);
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);

	struct device_node *np;
	struct resource res;

	dev_dbg(&op->dev, "stopping PPC-OF USB Controller\n");

	usb_remove_hcd(hcd);

	irq_dispose_mapping(hcd->irq);

	/* use request_mem_region to test if the ohci driver is loaded.  if so
	 * ensure the ohci core is operational.
	 */
	if (ehci->has_amcc_usb23) {
		np = of_find_compatible_node(NULL, NULL, "ibm,usb-ohci-440epx");
		if (np != NULL) {
			if (!of_address_to_resource(np, 0, &res))
				if (!request_mem_region(res.start,
							    0x4, hcd_name))
					set_ohci_hcfs(ehci, 1);
				else
					release_mem_region(res.start, 0x4);
			else
				pr_debug("%s: no ohci offset in fdt\n", __FILE__);
			of_node_put(np);
		}
	}
	usb_put_hcd(hcd);

	return 0;
}