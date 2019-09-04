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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_BAD_ADDR ; 

phys_addr_t pci_pio_to_address(unsigned long pio)
{
	phys_addr_t address = (phys_addr_t)OF_BAD_ADDR;

#ifdef PCI_IOBASE
	if (pio >= MMIO_UPPER_LIMIT)
		return address;

	address = logic_pio_to_hwaddr(pio);
#endif

	return address;
}