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
typedef  int /*<<< orphan*/  u32 ;
struct xen_pci_op {unsigned int devfn; int offset; int size; int /*<<< orphan*/  value; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; int /*<<< orphan*/  cmd; } ;
struct pcifront_sd {int dummy; } ;
struct pcifront_device {TYPE_1__* xdev; } ;
struct pci_bus {int /*<<< orphan*/  number; struct pcifront_sd* sysdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  XEN_PCI_OP_conf_read ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int do_pci_op (struct pcifront_device*,struct xen_pci_op*) ; 
 int errno_to_pcibios_err (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 struct pcifront_device* pcifront_get_pdev (struct pcifront_sd*) ; 
 scalar_t__ verbose_request ; 

__attribute__((used)) static int pcifront_bus_read(struct pci_bus *bus, unsigned int devfn,
			     int where, int size, u32 *val)
{
	int err = 0;
	struct xen_pci_op op = {
		.cmd    = XEN_PCI_OP_conf_read,
		.domain = pci_domain_nr(bus),
		.bus    = bus->number,
		.devfn  = devfn,
		.offset = where,
		.size   = size,
	};
	struct pcifront_sd *sd = bus->sysdata;
	struct pcifront_device *pdev = pcifront_get_pdev(sd);

	if (verbose_request)
		dev_info(&pdev->xdev->dev,
			 "read dev=%04x:%02x:%02x.%d - offset %x size %d\n",
			 pci_domain_nr(bus), bus->number, PCI_SLOT(devfn),
			 PCI_FUNC(devfn), where, size);

	err = do_pci_op(pdev, &op);

	if (likely(!err)) {
		if (verbose_request)
			dev_info(&pdev->xdev->dev, "read got back value %x\n",
				 op.value);

		*val = op.value;
	} else if (err == -ENODEV) {
		/* No device here, pretend that it just returned 0 */
		err = 0;
		*val = 0;
	}

	return errno_to_pcibios_err(err);
}