#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct slot {TYPE_2__* ctrl; } ;
struct pci_dev {int dummy; } ;
struct hotplug_slot {struct slot* private; } ;
struct TYPE_4__ {TYPE_1__* pcie; } ;
struct TYPE_3__ {struct pci_dev* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_config_pm_runtime_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (struct slot*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_adapter_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	struct slot *slot = hotplug_slot->private;
	struct pci_dev *pdev = slot->ctrl->pcie->port;

	pci_config_pm_runtime_get(pdev);
	pciehp_get_adapter_status(slot, value);
	pci_config_pm_runtime_put(pdev);
	return 0;
}