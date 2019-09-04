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
struct hotplug_slot {int /*<<< orphan*/  pci_slot; int /*<<< orphan*/  slot_list; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_remove_slot (int /*<<< orphan*/ ) ; 
 struct hotplug_slot* get_slot_from_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotplug_slot_name (struct hotplug_slot*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_hp_mutex ; 

void pci_hp_del(struct hotplug_slot *slot)
{
	struct hotplug_slot *temp;

	if (WARN_ON(!slot))
		return;

	mutex_lock(&pci_hp_mutex);
	temp = get_slot_from_name(hotplug_slot_name(slot));
	if (WARN_ON(temp != slot)) {
		mutex_unlock(&pci_hp_mutex);
		return;
	}

	list_del(&slot->slot_list);
	mutex_unlock(&pci_hp_mutex);
	dbg("Removed slot %s from the list\n", hotplug_slot_name(slot));
	fs_remove_slot(slot->pci_slot);
}