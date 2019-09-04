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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  match ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 unsigned int* cfg80211_find_ie_match (int /*<<< orphan*/ ,unsigned int const*,int,unsigned int*,int,int) ; 

const u8 *cfg80211_find_vendor_ie(unsigned int oui, int oui_type,
				  const u8 *ies, int len)
{
	const u8 *ie;
	u8 match[] = { oui >> 16, oui >> 8, oui, oui_type };
	int match_len = (oui_type < 0) ? 3 : sizeof(match);

	if (WARN_ON(oui_type > 0xff))
		return NULL;

	ie = cfg80211_find_ie_match(WLAN_EID_VENDOR_SPECIFIC, ies, len,
				    match, match_len, 2);

	if (ie && (ie[1] < 4))
		return NULL;

	return ie;
}