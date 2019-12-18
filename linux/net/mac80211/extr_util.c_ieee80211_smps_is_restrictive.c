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
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int IEEE80211_SMPS_AUTOMATIC ; 
#define  IEEE80211_SMPS_DYNAMIC 130 
#define  IEEE80211_SMPS_OFF 129 
#define  IEEE80211_SMPS_STATIC 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

bool ieee80211_smps_is_restrictive(enum ieee80211_smps_mode smps_mode_old,
				   enum ieee80211_smps_mode smps_mode_new)
{
	if (WARN_ON_ONCE(smps_mode_old == IEEE80211_SMPS_AUTOMATIC ||
			 smps_mode_new == IEEE80211_SMPS_AUTOMATIC))
		return false;

	switch (smps_mode_old) {
	case IEEE80211_SMPS_STATIC:
		return false;
	case IEEE80211_SMPS_DYNAMIC:
		return smps_mode_new == IEEE80211_SMPS_STATIC;
	case IEEE80211_SMPS_OFF:
		return smps_mode_new != IEEE80211_SMPS_OFF;
	default:
		WARN_ON(1);
	}

	return false;
}