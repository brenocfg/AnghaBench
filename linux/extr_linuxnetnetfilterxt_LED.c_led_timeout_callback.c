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
struct xt_led_info_internal {int /*<<< orphan*/  netfilter_led_trigger; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 struct xt_led_info_internal* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xt_led_info_internal* ledinternal ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void led_timeout_callback(struct timer_list *t)
{
	struct xt_led_info_internal *ledinternal = from_timer(ledinternal, t,
							      timer);

	led_trigger_event(&ledinternal->netfilter_led_trigger, LED_OFF);
}