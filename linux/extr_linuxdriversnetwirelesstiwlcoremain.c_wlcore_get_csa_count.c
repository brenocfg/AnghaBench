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
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_channel_sw_ie {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WLAN_EID_CHANNEL_SWITCH ; 
 int /*<<< orphan*/ * wlcore_get_beacon_ie (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wlcore_get_csa_count(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				u8 *csa_count)
{
	const u8 *ie;
	const struct ieee80211_channel_sw_ie *ie_csa;

	ie = wlcore_get_beacon_ie(wl, wlvif, WLAN_EID_CHANNEL_SWITCH);
	if (!ie)
		return -EINVAL;

	ie_csa = (struct ieee80211_channel_sw_ie *)&ie[2];
	*csa_count = ie_csa->count;

	return 0;
}