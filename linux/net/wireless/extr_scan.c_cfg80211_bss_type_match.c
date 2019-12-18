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
typedef  int u16 ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  enum ieee80211_bss_type { ____Placeholder_ieee80211_bss_type } ieee80211_bss_type ;

/* Variables and functions */
 int IEEE80211_BSS_TYPE_ANY ; 
#define  IEEE80211_BSS_TYPE_ESS 131 
#define  IEEE80211_BSS_TYPE_IBSS 130 
#define  IEEE80211_BSS_TYPE_MBSS 129 
#define  IEEE80211_BSS_TYPE_PBSS 128 
 int NL80211_BAND_60GHZ ; 
 int WLAN_CAPABILITY_DMG_TYPE_AP ; 
 int WLAN_CAPABILITY_DMG_TYPE_IBSS ; 
 int WLAN_CAPABILITY_DMG_TYPE_MASK ; 
 int WLAN_CAPABILITY_DMG_TYPE_PBSS ; 
 int WLAN_CAPABILITY_ESS ; 
 int WLAN_CAPABILITY_IBSS ; 

__attribute__((used)) static bool cfg80211_bss_type_match(u16 capability,
				    enum nl80211_band band,
				    enum ieee80211_bss_type bss_type)
{
	bool ret = true;
	u16 mask, val;

	if (bss_type == IEEE80211_BSS_TYPE_ANY)
		return ret;

	if (band == NL80211_BAND_60GHZ) {
		mask = WLAN_CAPABILITY_DMG_TYPE_MASK;
		switch (bss_type) {
		case IEEE80211_BSS_TYPE_ESS:
			val = WLAN_CAPABILITY_DMG_TYPE_AP;
			break;
		case IEEE80211_BSS_TYPE_PBSS:
			val = WLAN_CAPABILITY_DMG_TYPE_PBSS;
			break;
		case IEEE80211_BSS_TYPE_IBSS:
			val = WLAN_CAPABILITY_DMG_TYPE_IBSS;
			break;
		default:
			return false;
		}
	} else {
		mask = WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS;
		switch (bss_type) {
		case IEEE80211_BSS_TYPE_ESS:
			val = WLAN_CAPABILITY_ESS;
			break;
		case IEEE80211_BSS_TYPE_IBSS:
			val = WLAN_CAPABILITY_IBSS;
			break;
		case IEEE80211_BSS_TYPE_MBSS:
			val = 0;
			break;
		default:
			return false;
		}
	}

	ret = ((capability & mask) == val);
	return ret;
}