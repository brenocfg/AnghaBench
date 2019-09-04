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
struct phy_device {int phy_num_led_triggers; int /*<<< orphan*/ * led_link_trigger; int /*<<< orphan*/ * phy_led_triggers; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_led_trigger_unregister (int /*<<< orphan*/ *) ; 

void phy_led_triggers_unregister(struct phy_device *phy)
{
	int i;

	for (i = 0; i < phy->phy_num_led_triggers; i++)
		phy_led_trigger_unregister(&phy->phy_led_triggers[i]);

	if (phy->led_link_trigger)
		phy_led_trigger_unregister(phy->led_link_trigger);
}