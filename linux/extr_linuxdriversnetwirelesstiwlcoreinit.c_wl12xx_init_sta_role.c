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

/* Variables and functions */
 int wl1271_acx_conn_monit_params (struct wl1271*,struct wl12xx_vif*,int) ; 
 int wl1271_acx_group_address_tbl (struct wl1271*,struct wl12xx_vif*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wl1271_acx_rssi_snr_avg_weights (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_init_beacon_broadcast (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_init_sta_beacon_filter (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static int wl12xx_init_sta_role(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_group_address_tbl(wl, wlvif, true, NULL, 0);
	if (ret < 0)
		return ret;

	/* Initialize connection monitoring thresholds */
	ret = wl1271_acx_conn_monit_params(wl, wlvif, false);
	if (ret < 0)
		return ret;

	/* Beacon filtering */
	ret = wl1271_init_sta_beacon_filter(wl, wlvif);
	if (ret < 0)
		return ret;

	/* Beacons and broadcast settings */
	ret = wl1271_init_beacon_broadcast(wl, wlvif);
	if (ret < 0)
		return ret;

	/* Configure rssi/snr averaging weights */
	ret = wl1271_acx_rssi_snr_avg_weights(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}