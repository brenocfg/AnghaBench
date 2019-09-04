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
typedef  int u32 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 scalar_t__ pci_bus_crs_vendor_id (int) ; 
 scalar_t__ pci_bus_read_config_dword (struct pci_bus*,int,int /*<<< orphan*/ ,int*) ; 
 int pci_bus_wait_crs (struct pci_bus*,int,int*,int) ; 

bool pci_bus_generic_read_dev_vendor_id(struct pci_bus *bus, int devfn, u32 *l,
					int timeout)
{
	if (pci_bus_read_config_dword(bus, devfn, PCI_VENDOR_ID, l))
		return false;

	/* Some broken boards return 0 or ~0 if a slot is empty: */
	if (*l == 0xffffffff || *l == 0x00000000 ||
	    *l == 0x0000ffff || *l == 0xffff0000)
		return false;

	if (pci_bus_crs_vendor_id(*l))
		return pci_bus_wait_crs(bus, devfn, l, timeout);

	return true;
}