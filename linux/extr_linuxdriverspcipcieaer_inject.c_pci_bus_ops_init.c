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
struct pci_ops {int dummy; } ;
struct pci_bus_ops {struct pci_ops* ops; struct pci_bus* bus; int /*<<< orphan*/  list; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_bus_ops_init(struct pci_bus_ops *bus_ops,
			     struct pci_bus *bus,
			     struct pci_ops *ops)
{
	INIT_LIST_HEAD(&bus_ops->list);
	bus_ops->bus = bus;
	bus_ops->ops = ops;
}