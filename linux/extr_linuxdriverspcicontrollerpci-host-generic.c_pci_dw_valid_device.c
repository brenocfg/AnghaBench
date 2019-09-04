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
struct TYPE_2__ {scalar_t__ start; } ;
struct pci_config_window {TYPE_1__ busr; } ;
struct pci_bus {scalar_t__ number; struct pci_config_window* sysdata; } ;

/* Variables and functions */
 scalar_t__ PCI_SLOT (unsigned int) ; 

__attribute__((used)) static bool pci_dw_valid_device(struct pci_bus *bus, unsigned int devfn)
{
	struct pci_config_window *cfg = bus->sysdata;

	/*
	 * The Synopsys DesignWare PCIe controller in ECAM mode will not filter
	 * type 0 config TLPs sent to devices 1 and up on its downstream port,
	 * resulting in devices appearing multiple times on bus 0 unless we
	 * filter out those accesses here.
	 */
	if (bus->number == cfg->busr.start && PCI_SLOT(devfn) > 0)
		return false;

	return true;
}