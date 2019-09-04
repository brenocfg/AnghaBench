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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pci_bus_assign_resources (struct pci_bus const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pci_bus_assign_resources(const struct pci_bus *bus)
{
	__pci_bus_assign_resources(bus, NULL, NULL);
}