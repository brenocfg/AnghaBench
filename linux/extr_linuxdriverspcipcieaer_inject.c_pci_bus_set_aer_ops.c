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
struct pci_bus_ops {int /*<<< orphan*/  list; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pci_ops aer_inj_pci_ops ; 
 int /*<<< orphan*/  inject_lock ; 
 int /*<<< orphan*/  kfree (struct pci_bus_ops*) ; 
 struct pci_bus_ops* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_ops_init (struct pci_bus_ops*,struct pci_bus*,struct pci_ops*) ; 
 int /*<<< orphan*/  pci_bus_ops_list ; 
 struct pci_ops* pci_bus_set_ops (struct pci_bus*,struct pci_ops*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci_bus_set_aer_ops(struct pci_bus *bus)
{
	struct pci_ops *ops;
	struct pci_bus_ops *bus_ops;
	unsigned long flags;

	bus_ops = kmalloc(sizeof(*bus_ops), GFP_KERNEL);
	if (!bus_ops)
		return -ENOMEM;
	ops = pci_bus_set_ops(bus, &aer_inj_pci_ops);
	spin_lock_irqsave(&inject_lock, flags);
	if (ops == &aer_inj_pci_ops)
		goto out;
	pci_bus_ops_init(bus_ops, bus, ops);
	list_add(&bus_ops->list, &pci_bus_ops_list);
	bus_ops = NULL;
out:
	spin_unlock_irqrestore(&inject_lock, flags);
	kfree(bus_ops);
	return 0;
}