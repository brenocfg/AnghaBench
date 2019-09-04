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
struct phy_led_trigger {unsigned int speed; } ;
struct phy_device {unsigned int phy_num_led_triggers; struct phy_led_trigger* phy_led_triggers; } ;

/* Variables and functions */

__attribute__((used)) static struct phy_led_trigger *phy_speed_to_led_trigger(struct phy_device *phy,
							unsigned int speed)
{
	unsigned int i;

	for (i = 0; i < phy->phy_num_led_triggers; i++) {
		if (phy->phy_led_triggers[i].speed == speed)
			return &phy->phy_led_triggers[i];
	}
	return NULL;
}