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
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_P2P_CLIENT 131 
#define  NL80211_IFTYPE_P2P_DEVICE 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int RSI_OPMODE_AP ; 
 int RSI_OPMODE_P2P_CLIENT ; 
 int RSI_OPMODE_P2P_GO ; 
 int RSI_OPMODE_STA ; 
 int RSI_OPMODE_UNSUPPORTED ; 

__attribute__((used)) static int rsi_map_intf_mode(enum nl80211_iftype vif_type)
{
	switch (vif_type) {
	case NL80211_IFTYPE_STATION:
		return RSI_OPMODE_STA;
	case NL80211_IFTYPE_AP:
		return RSI_OPMODE_AP;
	case NL80211_IFTYPE_P2P_DEVICE:
		return RSI_OPMODE_P2P_CLIENT;
	case NL80211_IFTYPE_P2P_CLIENT:
		return RSI_OPMODE_P2P_CLIENT;
	case NL80211_IFTYPE_P2P_GO:
		return RSI_OPMODE_P2P_GO;
	default:
		return RSI_OPMODE_UNSUPPORTED;
	}
}