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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WLC_BAND_2G ; 
 int /*<<< orphan*/  WLC_BAND_5G ; 

__attribute__((used)) static u8 nl80211_band_to_fwil(enum nl80211_band band)
{
	switch (band) {
	case NL80211_BAND_2GHZ:
		return WLC_BAND_2G;
	case NL80211_BAND_5GHZ:
		return WLC_BAND_5G;
	default:
		WARN_ON(1);
		break;
	}
	return 0;
}