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
 int pciehp_reset_slot (struct slot*,int) ; 

__attribute__((used)) static int reset_slot(struct hotplug_slot *hotplug_slot, int probe)
{
	struct slot *slot = hotplug_slot->private;

	return pciehp_reset_slot(slot, probe);
}