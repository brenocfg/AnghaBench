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
struct asus_wmi {int /*<<< orphan*/  hotplug_workqueue; TYPE_1__* hotplug_slot; int /*<<< orphan*/  hotplug_work; } ;
struct TYPE_4__ {struct TYPE_4__* info; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/ * ops; struct asus_wmi* private; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asus_get_adapter_status (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_hotplug_slot_ops ; 
 int /*<<< orphan*/  asus_hotplug_work ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int) ; 
 int pci_hp_register (TYPE_1__*,struct pci_bus*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int asus_setup_pci_hotplug(struct asus_wmi *asus)
{
	int ret = -ENOMEM;
	struct pci_bus *bus = pci_find_bus(0, 1);

	if (!bus) {
		pr_err("Unable to find wifi PCI bus\n");
		return -ENODEV;
	}

	asus->hotplug_workqueue =
	    create_singlethread_workqueue("hotplug_workqueue");
	if (!asus->hotplug_workqueue)
		goto error_workqueue;

	INIT_WORK(&asus->hotplug_work, asus_hotplug_work);

	asus->hotplug_slot = kzalloc(sizeof(struct hotplug_slot), GFP_KERNEL);
	if (!asus->hotplug_slot)
		goto error_slot;

	asus->hotplug_slot->info = kzalloc(sizeof(struct hotplug_slot_info),
					   GFP_KERNEL);
	if (!asus->hotplug_slot->info)
		goto error_info;

	asus->hotplug_slot->private = asus;
	asus->hotplug_slot->ops = &asus_hotplug_slot_ops;
	asus_get_adapter_status(asus->hotplug_slot,
				&asus->hotplug_slot->info->adapter_status);

	ret = pci_hp_register(asus->hotplug_slot, bus, 0, "asus-wifi");
	if (ret) {
		pr_err("Unable to register hotplug slot - %d\n", ret);
		goto error_register;
	}

	return 0;

error_register:
	kfree(asus->hotplug_slot->info);
error_info:
	kfree(asus->hotplug_slot);
	asus->hotplug_slot = NULL;
error_slot:
	destroy_workqueue(asus->hotplug_workqueue);
error_workqueue:
	return ret;
}