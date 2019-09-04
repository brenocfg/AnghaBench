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
struct rtl_mac {scalar_t__ opmode; } ;
struct ieee80211_sta {scalar_t__ aid; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 

__attribute__((used)) static u8 _rtl_phydm_get_macid(struct rtl_priv *rtlpriv,
			       struct ieee80211_sta *sta)
{
	struct rtl_mac *mac = rtl_mac(rtlpriv);

	if (mac->opmode == NL80211_IFTYPE_STATION ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT) {
		return 0;
	} else if (mac->opmode == NL80211_IFTYPE_AP ||
		   mac->opmode == NL80211_IFTYPE_ADHOC)
		return sta->aid + 1;

	return 0;
}