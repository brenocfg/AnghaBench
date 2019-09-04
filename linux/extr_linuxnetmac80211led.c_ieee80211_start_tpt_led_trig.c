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
struct tpt_led_trigger {int running; int /*<<< orphan*/  timer; } ;
struct ieee80211_local {struct tpt_led_trigger* tpt_led_trigger; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  tpt_trig_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpt_trig_traffic (struct ieee80211_local*,struct tpt_led_trigger*) ; 

__attribute__((used)) static void ieee80211_start_tpt_led_trig(struct ieee80211_local *local)
{
	struct tpt_led_trigger *tpt_trig = local->tpt_led_trigger;

	if (tpt_trig->running)
		return;

	/* reset traffic */
	tpt_trig_traffic(local, tpt_trig);
	tpt_trig->running = true;

	tpt_trig_timer(&tpt_trig->timer);
	mod_timer(&tpt_trig->timer, round_jiffies(jiffies + HZ));
}