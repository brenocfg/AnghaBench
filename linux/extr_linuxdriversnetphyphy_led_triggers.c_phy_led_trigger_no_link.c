#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {TYPE_2__* last_triggered; TYPE_1__* led_link_trigger; } ;
struct TYPE_4__ {int /*<<< orphan*/  trigger; } ;
struct TYPE_3__ {int /*<<< orphan*/  trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_led_trigger_no_link(struct phy_device *phy)
{
	if (phy->last_triggered) {
		led_trigger_event(&phy->last_triggered->trigger, LED_OFF);
		led_trigger_event(&phy->led_link_trigger->trigger, LED_OFF);
		phy->last_triggered = NULL;
	}
}