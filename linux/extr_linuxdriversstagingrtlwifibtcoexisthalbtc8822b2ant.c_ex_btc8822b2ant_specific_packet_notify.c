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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ arp_cnt; } ;
struct TYPE_3__ {int wifi_is_high_pri_task; int specific_pkt_period_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 scalar_t__ BTC_PACKET_ARP ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b2ant_specific_packet_notify(struct btc_coexist *btcoexist,
					    u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool under_4way = false, wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (wifi_under_5g) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under 5G!!!\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (under_4way) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], specific Packet ---- under_4way!!\n");

		coex_sta->wifi_is_high_pri_task = true;
		coex_sta->specific_pkt_period_cnt = 2;

	} else if (type == BTC_PACKET_ARP) {
		coex_dm->arp_cnt++;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], specific Packet ARP notify -cnt = %d\n",
			 coex_dm->arp_cnt);

	} else {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], specific Packet DHCP or EAPOL notify [Type = %d]\n",
			type);

		coex_sta->wifi_is_high_pri_task = true;
		coex_sta->specific_pkt_period_cnt = 2;
	}

	if (coex_sta->wifi_is_high_pri_task)
		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
}