#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ kobj; } ;
struct pci_dev {TYPE_2__ dev; int /*<<< orphan*/  bus_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bridge_d3_update (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_free_resources (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_aspm_exit_link_state (struct pci_dev*) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_destroy_dev(struct pci_dev *dev)
{
	if (!dev->dev.kobj.parent)
		return;

	device_del(&dev->dev);

	down_write(&pci_bus_sem);
	list_del(&dev->bus_list);
	up_write(&pci_bus_sem);

	pcie_aspm_exit_link_state(dev);
	pci_bridge_d3_update(dev);
	pci_free_resources(dev);
	put_device(&dev->dev);
}