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
struct cfg80211_ap_settings {int ht_required; int vht_required; } ;

/* Variables and functions */
 int const BSS_MEMBERSHIP_SELECTOR_HT_PHY ; 
 int const BSS_MEMBERSHIP_SELECTOR_VHT_PHY ; 

__attribute__((used)) static void nl80211_check_ap_rate_selectors(struct cfg80211_ap_settings *params,
					    const u8 *rates)
{
	int i;

	if (!rates)
		return;

	for (i = 0; i < rates[1]; i++) {
		if (rates[2 + i] == BSS_MEMBERSHIP_SELECTOR_HT_PHY)
			params->ht_required = true;
		if (rates[2 + i] == BSS_MEMBERSHIP_SELECTOR_VHT_PHY)
			params->vht_required = true;
	}
}