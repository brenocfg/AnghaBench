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
struct phy_led_trigger {int /*<<< orphan*/  trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_trigger_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void phy_led_trigger_unregister(struct phy_led_trigger *plt)
{
	led_trigger_unregister(&plt->trigger);
}