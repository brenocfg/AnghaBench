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
struct wl1251 {int station_mode; int /*<<< orphan*/  listen_int; } ;
typedef  enum wl1251_station_mode { ____Placeholder_wl1251_station_mode } wl1251_station_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ACTIVE_MODE ; 
 int /*<<< orphan*/  CHIP_POWER_SAVE_MODE ; 
 int /*<<< orphan*/  CMD_DISCONNECT ; 
 int /*<<< orphan*/  DEBUG_PSM ; 
#define  STATION_ACTIVE_MODE 130 
#define  STATION_IDLE 129 
#define  STATION_POWER_SAVE_MODE 128 
 int /*<<< orphan*/  WAKE_UP_EVENT_DTIM_BITMAP ; 
 int /*<<< orphan*/  WL1251_ACX_BET_DISABLE ; 
 int /*<<< orphan*/  WL1251_ACX_BET_ENABLE ; 
 int /*<<< orphan*/  WL1251_DEFAULT_BET_CONSECUTIVE ; 
 int /*<<< orphan*/  WL1251_PSM_CAM ; 
 int /*<<< orphan*/  WL1251_PSM_ELP ; 
 int wl1251_acx_beacon_filter_opt (struct wl1251*,int) ; 
 int wl1251_acx_bet_enable (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_acx_sleep_auth (struct wl1251*,int /*<<< orphan*/ ) ; 
 int wl1251_acx_wake_up_conditions (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_ps_mode (struct wl1251*,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_template_set (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 

int wl1251_ps_set_mode(struct wl1251 *wl, enum wl1251_station_mode mode)
{
	int ret;

	switch (mode) {
	case STATION_POWER_SAVE_MODE:
		wl1251_debug(DEBUG_PSM, "entering psm");

		/* enable beacon filtering */
		ret = wl1251_acx_beacon_filter_opt(wl, true);
		if (ret < 0)
			return ret;

		ret = wl1251_acx_wake_up_conditions(wl,
						    WAKE_UP_EVENT_DTIM_BITMAP,
						    wl->listen_int);
		if (ret < 0)
			return ret;

		ret = wl1251_acx_bet_enable(wl, WL1251_ACX_BET_ENABLE,
					    WL1251_DEFAULT_BET_CONSECUTIVE);
		if (ret < 0)
			return ret;

		ret = wl1251_cmd_ps_mode(wl, CHIP_POWER_SAVE_MODE);
		if (ret < 0)
			return ret;

		ret = wl1251_acx_sleep_auth(wl, WL1251_PSM_ELP);
		if (ret < 0)
			return ret;
		break;
	case STATION_IDLE:
		wl1251_debug(DEBUG_PSM, "entering idle");

		ret = wl1251_acx_sleep_auth(wl, WL1251_PSM_ELP);
		if (ret < 0)
			return ret;

		ret = wl1251_cmd_template_set(wl, CMD_DISCONNECT, NULL, 0);
		if (ret < 0)
			return ret;
		break;
	case STATION_ACTIVE_MODE:
	default:
		wl1251_debug(DEBUG_PSM, "leaving psm");

		ret = wl1251_acx_sleep_auth(wl, WL1251_PSM_CAM);
		if (ret < 0)
			return ret;

		/* disable BET */
		ret = wl1251_acx_bet_enable(wl, WL1251_ACX_BET_DISABLE,
					    WL1251_DEFAULT_BET_CONSECUTIVE);
		if (ret < 0)
			return ret;

		/* disable beacon filtering */
		ret = wl1251_acx_beacon_filter_opt(wl, false);
		if (ret < 0)
			return ret;

		ret = wl1251_acx_wake_up_conditions(wl,
						    WAKE_UP_EVENT_DTIM_BITMAP,
						    wl->listen_int);
		if (ret < 0)
			return ret;

		ret = wl1251_cmd_ps_mode(wl, CHIP_ACTIVE_MODE);
		if (ret < 0)
			return ret;

		break;
	}
	wl->station_mode = mode;

	return ret;
}