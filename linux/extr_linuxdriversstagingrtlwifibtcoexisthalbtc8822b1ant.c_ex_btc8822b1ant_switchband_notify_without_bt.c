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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_SCAN_START_2G ; 
 scalar_t__ BTC_SWITCH_TO_24G_NOFORSCAN ; 
 scalar_t__ BTC_SWITCH_TO_5G ; 
 int /*<<< orphan*/  ex_btc8822b1ant_scan_notify_without_bt (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int,int) ; 

void ex_btc8822b1ant_switchband_notify_without_bt(struct btc_coexist *btcoexist,
						  u8 type)
{
	bool wifi_under_5g = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (type == BTC_SWITCH_TO_5G) {
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd, 0x3, 1);
		return;
	} else if (type == BTC_SWITCH_TO_24G_NOFORSCAN) {
		if (wifi_under_5g)

			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd,
							   0x3, 1);

		else
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd,
							   0x3, 2);
	} else {
		ex_btc8822b1ant_scan_notify_without_bt(btcoexist,
						       BTC_SCAN_START_2G);
	}
}