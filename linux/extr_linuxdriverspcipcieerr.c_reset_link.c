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
struct pcie_port_service_driver {scalar_t__ (* reset_link ) (struct pci_dev*) ;} ;
struct pci_dev {scalar_t__ hdr_type; scalar_t__ has_secondary_link; TYPE_1__* bus; } ;
typedef  scalar_t__ pci_ers_result_t ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ PCI_ERS_RESULT_DISCONNECT ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 scalar_t__ default_reset_link (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_printk (int /*<<< orphan*/ ,struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 struct pcie_port_service_driver* pcie_port_find_service (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t reset_link(struct pci_dev *dev, u32 service)
{
	struct pci_dev *udev;
	pci_ers_result_t status;
	struct pcie_port_service_driver *driver = NULL;

	if (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE) {
		/* Reset this port for all subordinates */
		udev = dev;
	} else {
		/* Reset the upstream component (likely downstream port) */
		udev = dev->bus->self;
	}

	/* Use the aer driver of the component firstly */
	driver = pcie_port_find_service(udev, service);

	if (driver && driver->reset_link) {
		status = driver->reset_link(udev);
	} else if (udev->has_secondary_link) {
		status = default_reset_link(udev);
	} else {
		pci_printk(KERN_DEBUG, dev, "no link-reset support at upstream device %s\n",
			pci_name(udev));
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (status != PCI_ERS_RESULT_RECOVERED) {
		pci_printk(KERN_DEBUG, dev, "link reset at upstream device %s failed\n",
			pci_name(udev));
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return status;
}