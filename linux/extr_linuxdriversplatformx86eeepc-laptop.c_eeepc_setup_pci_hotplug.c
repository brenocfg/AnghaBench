#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_bus {int dummy; } ;
struct hotplug_slot_info {int dummy; } ;
struct hotplug_slot {int dummy; } ;
struct eeepc_laptop {TYPE_1__* hotplug_slot; } ;
struct TYPE_4__ {struct TYPE_4__* info; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/ * ops; struct eeepc_laptop* private; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  eeepc_get_adapter_status (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeepc_hotplug_slot_ops ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int) ; 
 int pci_hp_register (TYPE_1__*,struct pci_bus*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int eeepc_setup_pci_hotplug(struct eeepc_laptop *eeepc)
{
	int ret = -ENOMEM;
	struct pci_bus *bus = pci_find_bus(0, 1);

	if (!bus) {
		pr_err("Unable to find wifi PCI bus\n");
		return -ENODEV;
	}

	eeepc->hotplug_slot = kzalloc(sizeof(struct hotplug_slot), GFP_KERNEL);
	if (!eeepc->hotplug_slot)
		goto error_slot;

	eeepc->hotplug_slot->info = kzalloc(sizeof(struct hotplug_slot_info),
					    GFP_KERNEL);
	if (!eeepc->hotplug_slot->info)
		goto error_info;

	eeepc->hotplug_slot->private = eeepc;
	eeepc->hotplug_slot->ops = &eeepc_hotplug_slot_ops;
	eeepc_get_adapter_status(eeepc->hotplug_slot,
				 &eeepc->hotplug_slot->info->adapter_status);

	ret = pci_hp_register(eeepc->hotplug_slot, bus, 0, "eeepc-wifi");
	if (ret) {
		pr_err("Unable to register hotplug slot - %d\n", ret);
		goto error_register;
	}

	return 0;

error_register:
	kfree(eeepc->hotplug_slot->info);
error_info:
	kfree(eeepc->hotplug_slot);
	eeepc->hotplug_slot = NULL;
error_slot:
	return ret;
}