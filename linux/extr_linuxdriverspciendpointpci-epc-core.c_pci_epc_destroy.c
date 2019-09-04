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
struct pci_epc {int /*<<< orphan*/  dev; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pci_epc*) ; 
 int /*<<< orphan*/  pci_ep_cfs_remove_epc_group (int /*<<< orphan*/ ) ; 

void pci_epc_destroy(struct pci_epc *epc)
{
	pci_ep_cfs_remove_epc_group(epc->group);
	device_unregister(&epc->dev);
	kfree(epc);
}