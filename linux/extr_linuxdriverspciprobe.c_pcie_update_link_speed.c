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
typedef  size_t u16 ;
struct pci_bus {int /*<<< orphan*/  cur_bus_speed; } ;

/* Variables and functions */
 size_t PCI_EXP_LNKSTA_CLS ; 
 int /*<<< orphan*/ * pcie_link_speed ; 

void pcie_update_link_speed(struct pci_bus *bus, u16 linksta)
{
	bus->cur_bus_speed = pcie_link_speed[linksta & PCI_EXP_LNKSTA_CLS];
}