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
struct wl1271 {int /*<<< orphan*/  dfs_region; } ;
struct wiphy {int dummy; } ;
struct regulatory_request {int /*<<< orphan*/  dfs_region; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 
 int /*<<< orphan*/  wlcore_regdomain_config (struct wl1271*) ; 

__attribute__((used)) static void wl1271_reg_notify(struct wiphy *wiphy,
			      struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct wl1271 *wl = hw->priv;

	/* copy the current dfs region */
	if (request)
		wl->dfs_region = request->dfs_region;

	wlcore_regdomain_config(wl);
}