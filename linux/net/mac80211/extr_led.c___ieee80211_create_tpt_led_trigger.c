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
struct tpt_led_trigger {char const* name; unsigned int blink_table_len; unsigned int want; int /*<<< orphan*/  timer; struct ieee80211_local* local; struct ieee80211_tpt_blink const* blink_table; } ;
struct ieee80211_tpt_blink {int dummy; } ;
struct TYPE_4__ {char const* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {struct tpt_led_trigger* tpt_led_trigger; TYPE_2__ tpt_led; TYPE_1__ hw; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (struct tpt_led_trigger*) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 struct tpt_led_trigger* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char const*,int,char*,char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpt_trig_timer ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

const char *
__ieee80211_create_tpt_led_trigger(struct ieee80211_hw *hw,
				   unsigned int flags,
				   const struct ieee80211_tpt_blink *blink_table,
				   unsigned int blink_table_len)
{
	struct ieee80211_local *local = hw_to_local(hw);
	struct tpt_led_trigger *tpt_trig;

	if (WARN_ON(local->tpt_led_trigger))
		return NULL;

	tpt_trig = kzalloc(sizeof(struct tpt_led_trigger), GFP_KERNEL);
	if (!tpt_trig)
		return NULL;

	snprintf(tpt_trig->name, sizeof(tpt_trig->name),
		 "%stpt", wiphy_name(local->hw.wiphy));

	local->tpt_led.name = tpt_trig->name;

	tpt_trig->blink_table = blink_table;
	tpt_trig->blink_table_len = blink_table_len;
	tpt_trig->want = flags;
	tpt_trig->local = local;

	timer_setup(&tpt_trig->timer, tpt_trig_timer, 0);

	local->tpt_led_trigger = tpt_trig;

	return tpt_trig->name;
}