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
typedef  enum ieee80211_ac_numbers { ____Placeholder_ieee80211_ac_numbers } ieee80211_ac_numbers ;

/* Variables and functions */
 int IEEE80211_AC_BE ; 
 int IEEE80211_AC_BK ; 
 int IEEE80211_AC_VI ; 
 int IEEE80211_AC_VO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static enum ieee80211_ac_numbers ieee80211_ac_from_wmm(int ac)
{
	switch (ac) {
	default:
		WARN_ON_ONCE(1);
		/* fall through */
	case 0:
		return IEEE80211_AC_BE;
	case 1:
		return IEEE80211_AC_BK;
	case 2:
		return IEEE80211_AC_VI;
	case 3:
		return IEEE80211_AC_VO;
	}
}