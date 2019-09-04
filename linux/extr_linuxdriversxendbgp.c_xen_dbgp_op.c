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
struct usb_hcd {int dummy; } ;
struct physdev_dbgp_op {int op; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_dbgp_op*) ; 
 int /*<<< orphan*/  PHYSDEVOP_DBGP_BUS_UNKNOWN ; 
 int /*<<< orphan*/  PHYSDEVOP_dbgp_op ; 
 int /*<<< orphan*/  xen_initial_domain () ; 

__attribute__((used)) static int xen_dbgp_op(struct usb_hcd *hcd, int op)
{
#ifdef CONFIG_PCI
	const struct device *ctrlr = hcd_to_bus(hcd)->controller;
#endif
	struct physdev_dbgp_op dbgp;

	if (!xen_initial_domain())
		return 0;

	dbgp.op = op;

#ifdef CONFIG_PCI
	if (dev_is_pci(ctrlr)) {
		const struct pci_dev *pdev = to_pci_dev(ctrlr);

		dbgp.u.pci.seg = pci_domain_nr(pdev->bus);
		dbgp.u.pci.bus = pdev->bus->number;
		dbgp.u.pci.devfn = pdev->devfn;
		dbgp.bus = PHYSDEVOP_DBGP_BUS_PCI;
	} else
#endif
		dbgp.bus = PHYSDEVOP_DBGP_BUS_UNKNOWN;

	return HYPERVISOR_physdev_op(PHYSDEVOP_dbgp_op, &dbgp);
}