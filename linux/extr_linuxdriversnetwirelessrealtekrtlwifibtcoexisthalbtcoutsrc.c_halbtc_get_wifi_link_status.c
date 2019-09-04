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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {scalar_t__ opmode; scalar_t__ link_state; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int WIFI_AP_CONNECTED ; 
 int WIFI_STA_CONNECTED ; 
 scalar_t__ is_any_client_connect_to_ap (struct btc_coexist*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 

__attribute__((used)) static u32 halbtc_get_wifi_link_status(struct btc_coexist *btcoexist)
{
	/* return value:
	 * [31:16] => connected port number
	 * [15:0]  => port connected bit define
	 */
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	u32 ret_val = 0;
	u32 port_connected_status = 0, num_of_connected_port = 0;

	if (mac->opmode == NL80211_IFTYPE_STATION &&
	    mac->link_state >= MAC80211_LINKED) {
		port_connected_status |= WIFI_STA_CONNECTED;
		num_of_connected_port++;
	}
	/* AP & ADHOC & MESH */
	if (is_any_client_connect_to_ap(btcoexist)) {
		port_connected_status |= WIFI_AP_CONNECTED;
		num_of_connected_port++;
	}
	/* TODO: P2P Connected Status */

	ret_val = (num_of_connected_port << 16) | port_connected_status;

	return ret_val;
}