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
struct btc_coexist {int dummy; } ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {int /*<<< orphan*/  bt_coex_thres2; int /*<<< orphan*/  bt_coex_thres; int /*<<< orphan*/  wifi_coex_thres2; int /*<<< orphan*/  wifi_coex_thres; } ;

/* Variables and functions */
 scalar_t__ BT_8822B_2ANT_BT_MAX_TX_POWER ; 
 int /*<<< orphan*/  BT_8822B_2ANT_BT_RSSI_COEXSWITCH_THRES1 ; 
 int /*<<< orphan*/  BT_8822B_2ANT_BT_RSSI_COEXSWITCH_THRES2 ; 
 scalar_t__ BT_8822B_2ANT_WIFI_MAX_TX_POWER ; 
 int /*<<< orphan*/  BT_8822B_2ANT_WIFI_RSSI_COEXSWITCH_THRES1 ; 
 int /*<<< orphan*/  BT_8822B_2ANT_WIFI_RSSI_COEXSWITCH_THRES2 ; 
 TYPE_1__* coex_sta ; 

__attribute__((used)) static void halbtc8822b2ant_coex_switch_threshold(struct btc_coexist *btcoexist,
						  u8 isolation_measuared)
{
	s8 interference_wl_tx = 0, interference_bt_tx = 0;

	interference_wl_tx =
		BT_8822B_2ANT_WIFI_MAX_TX_POWER - isolation_measuared;
	interference_bt_tx =
		BT_8822B_2ANT_BT_MAX_TX_POWER - isolation_measuared;

	coex_sta->wifi_coex_thres = BT_8822B_2ANT_WIFI_RSSI_COEXSWITCH_THRES1;
	coex_sta->wifi_coex_thres2 = BT_8822B_2ANT_WIFI_RSSI_COEXSWITCH_THRES2;

	coex_sta->bt_coex_thres = BT_8822B_2ANT_BT_RSSI_COEXSWITCH_THRES1;
	coex_sta->bt_coex_thres2 = BT_8822B_2ANT_BT_RSSI_COEXSWITCH_THRES2;
}