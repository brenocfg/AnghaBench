#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hotplug_slot {struct hotplug_slot* info; struct hotplug_slot* ops; } ;
struct controller {TYPE_1__* slot; } ;
struct TYPE_2__ {struct hotplug_slot* hotplug_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hotplug_slot*) ; 
 int /*<<< orphan*/  pci_hp_destroy (struct hotplug_slot*) ; 

__attribute__((used)) static void cleanup_slot(struct controller *ctrl)
{
	struct hotplug_slot *hotplug_slot = ctrl->slot->hotplug_slot;

	pci_hp_destroy(hotplug_slot);
	kfree(hotplug_slot->ops);
	kfree(hotplug_slot->info);
	kfree(hotplug_slot);
}