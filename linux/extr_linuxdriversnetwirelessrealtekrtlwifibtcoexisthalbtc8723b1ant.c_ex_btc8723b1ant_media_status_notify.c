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
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,scalar_t__*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_read_2byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_read_4byte ) (struct btc_coexist*,int) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__* wifi_chnl_info; scalar_t__ arp_cnt; int /*<<< orphan*/  backup_ampdu_max_time; int /*<<< orphan*/  backup_retry_limit; int /*<<< orphan*/  backup_arfr_cnt2; int /*<<< orphan*/  backup_arfr_cnt1; } ;
struct TYPE_3__ {int cck_ever_lock; scalar_t__ bt_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_B_MODE ; 
 int /*<<< orphan*/  BTC_GET_U1_WIFI_CENTRAL_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 scalar_t__ BTC_MEDIA_CONNECT ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int) ; 

void ex_btc8723b1ant_media_status_notify(struct btc_coexist *btcoexist,
					 u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[3] = {0};
	u32 wifi_bw;
	u8 wifi_central_chnl;
	bool wifi_under_b_mode = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		return;

	if (type == BTC_MEDIA_CONNECT) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], MEDIA connect notify\n");
		/* Force antenna setup for no scan result issue */
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     FORCE_EXEC, false, false);
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
			 "[BTCoex], MEDIA disconnect notify\n");
		coex_dm->arp_cnt = 0;

		btcoexist->btc_write_1byte(btcoexist, 0x6cd, 0x0); /* CCK Tx */
		btcoexist->btc_write_1byte(btcoexist, 0x6cf, 0x0); /* CCK Rx */

		coex_sta->cck_ever_lock = false;
	}

	/* only 2.4G we need to inform bt the chnl mask */
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wifi_central_chnl);

	if (type == BTC_MEDIA_CONNECT && wifi_central_chnl <= 14) {
		h2c_parameter[0] = 0x0;
		h2c_parameter[1] = wifi_central_chnl;
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);
		if (BTC_WIFI_BW_HT40 == wifi_bw)
			h2c_parameter[2] = 0x30;
		else
			h2c_parameter[2] = 0x20;
	}

	coex_dm->wifi_chnl_info[0] = h2c_parameter[0];
	coex_dm->wifi_chnl_info[1] = h2c_parameter[1];
	coex_dm->wifi_chnl_info[2] = h2c_parameter[2];

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], FW write 0x66 = 0x%x\n",
		 h2c_parameter[0] << 16 | h2c_parameter[1] << 8 |
		 h2c_parameter[2]);

	btcoexist->btc_fill_h2c(btcoexist, 0x66, 3, h2c_parameter);
}