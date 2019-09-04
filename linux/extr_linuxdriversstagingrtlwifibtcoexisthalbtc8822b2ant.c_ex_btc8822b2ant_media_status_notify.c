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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_B_MODE ; 
 scalar_t__ BTC_MEDIA_CONNECT ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_update_wifi_ch_info (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int) ; 

void ex_btc8822b2ant_media_status_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_b_mode = false, wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (type == BTC_MEDIA_CONNECT) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], MEDIA connect notify\n");

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);

		if (wifi_under_5g) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], WiFi is under 5G!!!\n");

			halbtc8822b2ant_action_wifi_under5g(btcoexist);
			return;
		}

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_2G_RUNTIME);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
				   &wifi_under_b_mode);

		/* Set CCK Tx/Rx high Pri except 11b mode */
		if (wifi_under_b_mode) {
			btcoexist->btc_write_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_write_1byte(btcoexist, 0x6cf,
						   0x00); /* CCK Rx */
		} else {
			btcoexist->btc_write_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_write_1byte(btcoexist, 0x6cf,
						   0x10); /* CCK Rx */
		}

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], MEDIA disconnect notify\n");

		btcoexist->btc_write_1byte(btcoexist, 0x6cd, 0x0); /* CCK Tx */
		btcoexist->btc_write_1byte(btcoexist, 0x6cf, 0x0); /* CCK Rx */

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
	}

	halbtc8822b2ant_update_wifi_ch_info(btcoexist, type);
}