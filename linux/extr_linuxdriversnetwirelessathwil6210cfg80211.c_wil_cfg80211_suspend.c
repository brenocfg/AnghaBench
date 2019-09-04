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
struct wiphy {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vif_mutex; int /*<<< orphan*/  status; } ;
struct cfg80211_wowlan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_abort_scan_all_vifs (struct wil6210_priv*,int) ; 
 int wil_can_suspend (struct wil6210_priv*,int) ; 
 int /*<<< orphan*/  wil_dbg_pm (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_p2p_stop_radio_operations (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_status_suspended ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_suspend(struct wiphy *wiphy,
				struct cfg80211_wowlan *wow)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	int rc;

	/* Setting the wakeup trigger based on wow is TBD */

	if (test_bit(wil_status_suspended, wil->status)) {
		wil_dbg_pm(wil, "trying to suspend while suspended\n");
		return 0;
	}

	rc = wil_can_suspend(wil, false);
	if (rc)
		goto out;

	wil_dbg_pm(wil, "suspending\n");

	mutex_lock(&wil->mutex);
	mutex_lock(&wil->vif_mutex);
	wil_p2p_stop_radio_operations(wil);
	wil_abort_scan_all_vifs(wil, true);
	mutex_unlock(&wil->vif_mutex);
	mutex_unlock(&wil->mutex);

out:
	return rc;
}