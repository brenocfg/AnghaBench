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
struct xt_led_info_internal {int /*<<< orphan*/  netfilter_led_trigger; int /*<<< orphan*/  timer; } ;
struct xt_led_info {scalar_t__ delay; scalar_t__ always_blink; struct xt_led_info_internal* internal_data; } ;
struct xt_action_param {struct xt_led_info* targinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 unsigned int XT_CONTINUE ; 
 unsigned long XT_LED_BLINK_DELAY ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_trigger_blink_oneshot (int /*<<< orphan*/ *,unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
led_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_led_info *ledinfo = par->targinfo;
	struct xt_led_info_internal *ledinternal = ledinfo->internal_data;
	unsigned long led_delay = XT_LED_BLINK_DELAY;

	/*
	 * If "always blink" is enabled, and there's still some time until the
	 * LED will switch off, briefly switch it off now.
	 */
	if ((ledinfo->delay > 0) && ledinfo->always_blink &&
	    timer_pending(&ledinternal->timer))
		led_trigger_blink_oneshot(&ledinternal->netfilter_led_trigger,
					  &led_delay, &led_delay, 1);
	else
		led_trigger_event(&ledinternal->netfilter_led_trigger, LED_FULL);

	/* If there's a positive delay, start/update the timer */
	if (ledinfo->delay > 0) {
		mod_timer(&ledinternal->timer,
			  jiffies + msecs_to_jiffies(ledinfo->delay));

	/* Otherwise if there was no delay given, blink as fast as possible */
	} else if (ledinfo->delay == 0) {
		led_trigger_event(&ledinternal->netfilter_led_trigger, LED_OFF);
	}

	/* else the delay is negative, which means switch on and stay on */

	return XT_CONTINUE;
}