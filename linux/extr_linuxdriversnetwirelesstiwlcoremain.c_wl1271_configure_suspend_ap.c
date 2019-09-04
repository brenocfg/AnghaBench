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
struct wl12xx_vif {int /*<<< orphan*/  flags; } ;
struct wl1271 {int dummy; } ;
struct cfg80211_wowlan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLVIF_FLAG_AP_STARTED ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_acx_beacon_filter_opt (struct wl1271*,struct wl12xx_vif*,int) ; 
 int wl1271_configure_wowlan (struct wl1271*,struct cfg80211_wowlan*) ; 

__attribute__((used)) static int wl1271_configure_suspend_ap(struct wl1271 *wl,
					struct wl12xx_vif *wlvif,
					struct cfg80211_wowlan *wow)
{
	int ret = 0;

	if (!test_bit(WLVIF_FLAG_AP_STARTED, &wlvif->flags))
		goto out;

	ret = wl1271_acx_beacon_filter_opt(wl, wlvif, true);
	if (ret < 0)
		goto out;

	ret = wl1271_configure_wowlan(wl, wow);
	if (ret < 0)
		goto out;

out:
	return ret;

}