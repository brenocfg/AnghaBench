#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,scalar_t__*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_2__ {scalar_t__* wifi_chnl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_WIFI_CENTRAL_CHNL ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 scalar_t__ BTC_MEDIA_CONNECT ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,scalar_t__*) ; 

__attribute__((used)) static void halbtc8822b2ant_update_wifi_ch_info(struct btc_coexist *btcoexist,
						u8 type)
{
	u8 h2c_parameter[3] = {0};
	u32 wifi_bw;
	u8 wifi_central_chnl;
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	/* only 2.4G we need to inform bt the chnl mask */
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wifi_central_chnl);
	if ((type == BTC_MEDIA_CONNECT) && (wifi_central_chnl <= 14)) {
		/* enable BT AFH skip WL channel for 8822b
		 * because BT Rx LO interference
		 */
		h2c_parameter[0] = 0x1;
		h2c_parameter[1] = wifi_central_chnl;
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);
		if (wifi_bw == BTC_WIFI_BW_HT40)
			h2c_parameter[2] = 0x30;
		else
			h2c_parameter[2] = 0x20;
	}

	coex_dm->wifi_chnl_info[0] = h2c_parameter[0];
	coex_dm->wifi_chnl_info[1] = h2c_parameter[1];
	coex_dm->wifi_chnl_info[2] = h2c_parameter[2];

	btcoexist->btc_fill_h2c(btcoexist, 0x66, 3, h2c_parameter);
}