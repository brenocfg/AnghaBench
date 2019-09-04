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
struct slot {int dummy; } ;
struct hotplug_slot {struct slot* private; } ;

/* Variables and functions */
 int pciehp_sysfs_enable_slot (struct slot*) ; 

__attribute__((used)) static int enable_slot(struct hotplug_slot *hotplug_slot)
{
	struct slot *slot = hotplug_slot->private;

	return pciehp_sysfs_enable_slot(slot);
}