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
typedef  enum nl80211_smps_mode { ____Placeholder_nl80211_smps_mode } nl80211_smps_mode ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
#define  IEEE80211_SMPS_DYNAMIC 130 
#define  IEEE80211_SMPS_OFF 129 
#define  IEEE80211_SMPS_STATIC 128 
 int NL80211_SMPS_DYNAMIC ; 
 int NL80211_SMPS_OFF ; 
 int NL80211_SMPS_STATIC ; 

enum nl80211_smps_mode
ieee80211_smps_mode_to_smps_mode(enum ieee80211_smps_mode smps)
{
	switch (smps) {
	case IEEE80211_SMPS_OFF:
		return NL80211_SMPS_OFF;
	case IEEE80211_SMPS_STATIC:
		return NL80211_SMPS_STATIC;
	case IEEE80211_SMPS_DYNAMIC:
		return NL80211_SMPS_DYNAMIC;
	default:
		return NL80211_SMPS_OFF;
	}
}