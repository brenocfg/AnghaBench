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
typedef  int u8 ;
struct ieee80211_network {scalar_t__ broadcom_cap_exist; } ;

/* Variables and functions */

__attribute__((used)) static u8 HTIOTActIsMgntUseCCK6M(struct ieee80211_network *network)
{
	u8	retValue = 0;

	// 2008/01/25 MH Judeg if we need to use OFDM to sned MGNT frame for broadcom AP.
	// 2008/01/28 MH We must prevent that we select null bssid to link.

	if (network->broadcom_cap_exist)
		retValue = 1;

	return retValue;
}