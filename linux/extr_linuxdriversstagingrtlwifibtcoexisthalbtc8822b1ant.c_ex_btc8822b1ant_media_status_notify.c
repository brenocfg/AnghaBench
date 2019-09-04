#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_read_2byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ arp_cnt; int /*<<< orphan*/  backup_ampdu_max_time; int /*<<< orphan*/  backup_retry_limit; int /*<<< orphan*/  backup_arfr_cnt2; int /*<<< orphan*/  backup_arfr_cnt1; } ;
struct TYPE_3__ {int cck_ever_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_B_MODE ; 
 scalar_t__ BTC_MEDIA_CONNECT ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_update_wifi_ch_info (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int) ; 

void ex_btc8822b1ant_media_status_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_b_mode = false;
	bool wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (type == BTC_MEDIA_CONNECT) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], 2g media connect notify");

		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE, true);

		if (wifi_under_5g) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], 5g media notify\n");

			halbtc8822b1ant_action_wifi_under5g(btcoexist);
			return;
		}
		/* Force antenna setup for no scan result issue */
		halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_1ANT_PHASE_2G_RUNTIME);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
				   &wifi_under_b_mode);

		/* Set CCK Tx/Rx high Pri except 11b mode */
		if (wifi_under_b_mode) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** (media status notity under b mode) **********\n");
			btcoexist->btc_write_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_write_1byte(btcoexist, 0x6cf,
						   0x00); /* CCK Rx */
		} else {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** (media status notity not under b mode) **********\n");
			btcoexist->btc_write_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_write_1byte(btcoexist, 0x6cf,
						   0x10); /* CCK Rx */
		}

		coex_dm->backup_arfr_cnt1 =
			btcoexist->btc_read_4byte(btcoexist, 0x430);
		coex_dm->backup_arfr_cnt2 =
			btcoexist->btc_read_4byte(btcoexist, 0x434);
		coex_dm->backup_retry_limit =
			btcoexist->btc_read_2byte(btcoexist, 0x42a);
		coex_dm->backup_ampdu_max_time =
			btcoexist->btc_read_1byte(btcoexist, 0x456);
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], 2g media disconnect notify\n");
		coex_dm->arp_cnt = 0;

		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE, false);

		btcoexist->btc_write_1byte(btcoexist, 0x6cd, 0x0); /* CCK Tx */
		btcoexist->btc_write_1byte(btcoexist, 0x6cf, 0x0); /* CCK Rx */

		coex_sta->cck_ever_lock = false;
	}

	halbtc8822b1ant_update_wifi_ch_info(btcoexist, type);
}