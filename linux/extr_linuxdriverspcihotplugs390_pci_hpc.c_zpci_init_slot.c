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
struct zpci_dev {int fid; int /*<<< orphan*/  bus; } ;
struct slot {int /*<<< orphan*/  slot_list; struct slot* hotplug_slot; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  power_status; int /*<<< orphan*/ * ops; struct slot* info; struct zpci_dev* zdev; struct slot* private; } ;
struct hotplug_slot_info {int /*<<< orphan*/  slot_list; struct hotplug_slot_info* hotplug_slot; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  power_status; int /*<<< orphan*/ * ops; struct hotplug_slot_info* info; struct zpci_dev* zdev; struct hotplug_slot_info* private; } ;
struct hotplug_slot {int /*<<< orphan*/  slot_list; struct hotplug_slot* hotplug_slot; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  power_status; int /*<<< orphan*/ * ops; struct hotplug_slot* info; struct zpci_dev* zdev; struct hotplug_slot* private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  ZPCI_DEVFN ; 
 int /*<<< orphan*/  get_adapter_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_power_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pci_hp_register (struct slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  s390_hotplug_slot_list ; 
 int /*<<< orphan*/  s390_hotplug_slot_ops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int zpci_init_slot(struct zpci_dev *zdev)
{
	struct hotplug_slot *hotplug_slot;
	struct hotplug_slot_info *info;
	char name[SLOT_NAME_SIZE];
	struct slot *slot;
	int rc;

	if (!zdev)
		return 0;

	slot = kzalloc(sizeof(*slot), GFP_KERNEL);
	if (!slot)
		goto error;

	hotplug_slot = kzalloc(sizeof(*hotplug_slot), GFP_KERNEL);
	if (!hotplug_slot)
		goto error_hp;
	hotplug_slot->private = slot;

	slot->hotplug_slot = hotplug_slot;
	slot->zdev = zdev;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		goto error_info;
	hotplug_slot->info = info;

	hotplug_slot->ops = &s390_hotplug_slot_ops;

	get_power_status(hotplug_slot, &info->power_status);
	get_adapter_status(hotplug_slot, &info->adapter_status);

	snprintf(name, SLOT_NAME_SIZE, "%08x", zdev->fid);
	rc = pci_hp_register(slot->hotplug_slot, zdev->bus,
			     ZPCI_DEVFN, name);
	if (rc)
		goto error_reg;

	list_add(&slot->slot_list, &s390_hotplug_slot_list);
	return 0;

error_reg:
	kfree(info);
error_info:
	kfree(hotplug_slot);
error_hp:
	kfree(slot);
error:
	return -ENOMEM;
}