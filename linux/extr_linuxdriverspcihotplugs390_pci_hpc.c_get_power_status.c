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
typedef  int u8 ;
struct slot {TYPE_1__* zdev; } ;
struct hotplug_slot {struct slot* private; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
#define  ZPCI_FN_STATE_STANDBY 128 

__attribute__((used)) static int get_power_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	struct slot *slot = hotplug_slot->private;

	switch (slot->zdev->state) {
	case ZPCI_FN_STATE_STANDBY:
		*value = 0;
		break;
	default:
		*value = 1;
		break;
	}
	return 0;
}