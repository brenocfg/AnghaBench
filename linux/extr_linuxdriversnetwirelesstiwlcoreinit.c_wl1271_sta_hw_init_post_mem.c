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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int wl1271_acx_keep_alive_mode (struct wl1271*,struct wl12xx_vif*,int) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static int wl1271_sta_hw_init_post_mem(struct wl1271 *wl,
				       struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	/* disable the keep-alive feature */
	ret = wl1271_acx_keep_alive_mode(wl, wlvif, false);
	if (ret < 0)
		return ret;

	return 0;
}