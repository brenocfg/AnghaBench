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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; struct wl12xx_vif* sched_vif; TYPE_1__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_scan_ies {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct cfg80211_sched_scan_request {int dummy; } ;
struct TYPE_2__ {int (* sched_scan_start ) (struct wl1271*,struct wl12xx_vif*,struct cfg80211_sched_scan_request*,struct ieee80211_scan_ies*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EAGAIN ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int stub1 (struct wl1271*,struct wl12xx_vif*,struct cfg80211_sched_scan_request*,struct ieee80211_scan_ies*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static int wl1271_op_sched_scan_start(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct cfg80211_sched_scan_request *req,
				      struct ieee80211_scan_ies *ies)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	wl1271_debug(DEBUG_MAC80211, "wl1271_op_sched_scan_start");

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EAGAIN;
		goto out;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	ret = wl->ops->sched_scan_start(wl, wlvif, req, ies);
	if (ret < 0)
		goto out_sleep;

	wl->sched_vif = wlvif;

out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	return ret;
}