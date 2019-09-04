#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct pci_bus {TYPE_3__* self; TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcibios_get_phb_of_node (struct pci_bus*) ; 

void pci_set_bus_of_node(struct pci_bus *bus)
{
	if (bus->self == NULL)
		bus->dev.of_node = pcibios_get_phb_of_node(bus);
	else
		bus->dev.of_node = of_node_get(bus->self->dev.of_node);
}