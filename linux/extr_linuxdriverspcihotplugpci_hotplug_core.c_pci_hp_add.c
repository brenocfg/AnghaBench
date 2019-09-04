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
struct pci_slot {int /*<<< orphan*/  kobj; } ;
struct hotplug_slot {int /*<<< orphan*/  slot_list; struct pci_slot* pci_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int fs_add_slot (struct pci_slot*) ; 
 int /*<<< orphan*/  hotplug_slot_name (struct hotplug_slot*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_hotplug_slot_list ; 
 int /*<<< orphan*/  pci_hp_mutex ; 

int pci_hp_add(struct hotplug_slot *slot)
{
	struct pci_slot *pci_slot = slot->pci_slot;
	int result;

	result = fs_add_slot(pci_slot);
	if (result)
		return result;

	kobject_uevent(&pci_slot->kobj, KOBJ_ADD);
	mutex_lock(&pci_hp_mutex);
	list_add(&slot->slot_list, &pci_hotplug_slot_list);
	mutex_unlock(&pci_hp_mutex);
	dbg("Added slot %s to the list\n", hotplug_slot_name(slot));
	return 0;
}