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
struct TYPE_2__ {scalar_t__ name; } ;
struct ieee80211_local {scalar_t__ tpt_led_trigger; TYPE_1__ tpt_led; TYPE_1__ rx_led; TYPE_1__ tx_led; TYPE_1__ assoc_led; TYPE_1__ radio_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  led_trigger_unregister (TYPE_1__*) ; 

void ieee80211_led_exit(struct ieee80211_local *local)
{
	if (local->radio_led.name)
		led_trigger_unregister(&local->radio_led);
	if (local->assoc_led.name)
		led_trigger_unregister(&local->assoc_led);
	if (local->tx_led.name)
		led_trigger_unregister(&local->tx_led);
	if (local->rx_led.name)
		led_trigger_unregister(&local->rx_led);

	if (local->tpt_led_trigger) {
		led_trigger_unregister(&local->tpt_led);
		kfree(local->tpt_led_trigger);
	}
}