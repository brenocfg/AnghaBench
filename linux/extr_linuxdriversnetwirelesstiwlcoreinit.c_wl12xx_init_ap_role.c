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
struct wl12xx_vif {int /*<<< orphan*/  power_level; } ;
struct wl1271 {scalar_t__ radar_debug_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLCORE_CFG_FEATURE_RADAR_DEBUG ; 
 int wl1271_acx_ap_max_tx_retry (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_acx_tx_power (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_cmd_generic_cfg (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl12xx_init_ap_role(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_ap_max_tx_retry(wl, wlvif);
	if (ret < 0)
		return ret;

	/* initialize Tx power */
	ret = wl1271_acx_tx_power(wl, wlvif, wlvif->power_level);
	if (ret < 0)
		return ret;

	if (wl->radar_debug_mode)
		wlcore_cmd_generic_cfg(wl, wlvif,
				       WLCORE_CFG_FEATURE_RADAR_DEBUG,
				       wl->radar_debug_mode, 0);

	return 0;
}