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
struct hotplug_slot_info {int dummy; } ;
struct hotplug_slot {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct hotplug_slot_info*,int) ; 

int pci_hp_change_slot_info(struct hotplug_slot *slot,
			    struct hotplug_slot_info *info)
{
	if (!slot || !info)
		return -ENODEV;

	memcpy(slot->info, info, sizeof(struct hotplug_slot_info));

	return 0;
}