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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledtrig_tx ; 
 int /*<<< orphan*/  ledtrig_tx_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int tx_activity ; 

__attribute__((used)) static void at76_ledtrig_tx_timerfunc(struct timer_list *unused)
{
	static int tx_lastactivity;

	if (tx_lastactivity != tx_activity) {
		tx_lastactivity = tx_activity;
		led_trigger_event(ledtrig_tx, LED_FULL);
		mod_timer(&ledtrig_tx_timer, jiffies + HZ / 4);
	} else
		led_trigger_event(ledtrig_tx, LED_OFF);
}