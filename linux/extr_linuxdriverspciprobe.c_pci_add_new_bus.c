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
struct pci_dev {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  children; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pci_bus* pci_alloc_child_bus (struct pci_bus*,struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct pci_bus *pci_add_new_bus(struct pci_bus *parent, struct pci_dev *dev,
				int busnr)
{
	struct pci_bus *child;

	child = pci_alloc_child_bus(parent, dev, busnr);
	if (child) {
		down_write(&pci_bus_sem);
		list_add_tail(&child->node, &parent->children);
		up_write(&pci_bus_sem);
	}
	return child;
}