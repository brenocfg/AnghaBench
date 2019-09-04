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
struct ieee80211_conf {int flags; } ;
struct TYPE_2__ {struct ieee80211_conf conf; } ;
struct ieee80211_local {int /*<<< orphan*/  dynamic_ps_enable_work; int /*<<< orphan*/  dynamic_ps_timer; scalar_t__ ps_sdata; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_enable_ps (struct ieee80211_local*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_change_ps(struct ieee80211_local *local)
{
	struct ieee80211_conf *conf = &local->hw.conf;

	if (local->ps_sdata) {
		ieee80211_enable_ps(local, local->ps_sdata);
	} else if (conf->flags & IEEE80211_CONF_PS) {
		conf->flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
		del_timer_sync(&local->dynamic_ps_timer);
		cancel_work_sync(&local->dynamic_ps_enable_work);
	}
}