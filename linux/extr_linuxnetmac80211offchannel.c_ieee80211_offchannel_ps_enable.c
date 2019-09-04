#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_if_managed {int /*<<< orphan*/  conn_mon_timer; int /*<<< orphan*/  bcn_mon_timer; } ;
struct TYPE_4__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_2__ conf; } ;
struct ieee80211_local {int offchannel_ps_enabled; TYPE_3__ hw; int /*<<< orphan*/  dynamic_ps_enable_work; int /*<<< orphan*/  dynamic_ps_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  PS_NULLFUNC_STACK ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_hw_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_nullfunc (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 

__attribute__((used)) static void ieee80211_offchannel_ps_enable(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	local->offchannel_ps_enabled = false;

	/* FIXME: what to do when local->pspolling is true? */

	del_timer_sync(&local->dynamic_ps_timer);
	del_timer_sync(&ifmgd->bcn_mon_timer);
	del_timer_sync(&ifmgd->conn_mon_timer);

	cancel_work_sync(&local->dynamic_ps_enable_work);

	if (local->hw.conf.flags & IEEE80211_CONF_PS) {
		local->offchannel_ps_enabled = true;
		local->hw.conf.flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	}

	if (!local->offchannel_ps_enabled ||
	    !ieee80211_hw_check(&local->hw, PS_NULLFUNC_STACK))
		/*
		 * If power save was enabled, no need to send a nullfunc
		 * frame because AP knows that we are sleeping. But if the
		 * hardware is creating the nullfunc frame for power save
		 * status (ie. IEEE80211_HW_PS_NULLFUNC_STACK is not
		 * enabled) and power save was enabled, the firmware just
		 * sent a null frame with power save disabled. So we need
		 * to send a new nullfunc frame to inform the AP that we
		 * are again sleeping.
		 */
		ieee80211_send_nullfunc(local, sdata, true);
}