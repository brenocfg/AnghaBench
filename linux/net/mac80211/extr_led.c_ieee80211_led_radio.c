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
struct ieee80211_local {int /*<<< orphan*/  radio_led; int /*<<< orphan*/  radio_led_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ieee80211_led_radio(struct ieee80211_local *local, bool enabled)
{
	if (!atomic_read(&local->radio_led_active))
		return;
	if (enabled)
		led_trigger_event(&local->radio_led, LED_FULL);
	else
		led_trigger_event(&local->radio_led, LED_OFF);
}