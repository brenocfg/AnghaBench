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
struct ieee80211_local {int /*<<< orphan*/  workqueue; int /*<<< orphan*/  reconfig_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TPT_LEDTRIG_FL_RADIO ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_stop (struct ieee80211_local*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_led_radio (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  ieee80211_mod_tpt_led_trig (struct ieee80211_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_stop_device(struct ieee80211_local *local)
{
	ieee80211_led_radio(local, false);
	ieee80211_mod_tpt_led_trig(local, 0, IEEE80211_TPT_LEDTRIG_FL_RADIO);

	cancel_work_sync(&local->reconfig_filter);

	flush_workqueue(local->workqueue);
	drv_stop(local);
}