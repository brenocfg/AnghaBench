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
struct xen_pcibk_device {struct vpci_dev_data* pci_dev_data; } ;
struct vpci_dev_data {int /*<<< orphan*/ * dev_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PCI_SLOT_MAX ; 
 struct vpci_dev_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __xen_pcibk_init_devices(struct xen_pcibk_device *pdev)
{
	int slot;
	struct vpci_dev_data *vpci_dev;

	vpci_dev = kmalloc(sizeof(*vpci_dev), GFP_KERNEL);
	if (!vpci_dev)
		return -ENOMEM;

	mutex_init(&vpci_dev->lock);

	for (slot = 0; slot < PCI_SLOT_MAX; slot++)
		INIT_LIST_HEAD(&vpci_dev->dev_list[slot]);

	pdev->pci_dev_data = vpci_dev;

	return 0;
}