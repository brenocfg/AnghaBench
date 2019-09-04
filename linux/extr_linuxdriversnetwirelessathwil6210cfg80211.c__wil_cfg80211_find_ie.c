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
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_vendor_ie {int* oui; int /*<<< orphan*/  oui_type; } ;

/* Variables and functions */
 int const WLAN_EID_VENDOR_SPECIFIC ; 
 int const* cfg80211_find_ie (int const,int const*,int) ; 
 int const* cfg80211_find_vendor_ie (int,int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static const u8 *_wil_cfg80211_find_ie(const u8 *ies, u16 ies_len, const u8 *ie,
				       u16 ie_len)
{
	struct ieee80211_vendor_ie *vie;
	u32 oui;

	/* IE tag at offset 0, length at offset 1 */
	if (ie_len < 2 || 2 + ie[1] > ie_len)
		return NULL;

	if (ie[0] != WLAN_EID_VENDOR_SPECIFIC)
		return cfg80211_find_ie(ie[0], ies, ies_len);

	/* make sure there is room for 3 bytes OUI + 1 byte OUI type */
	if (ie[1] < 4)
		return NULL;
	vie = (struct ieee80211_vendor_ie *)ie;
	oui = vie->oui[0] << 16 | vie->oui[1] << 8 | vie->oui[2];
	return cfg80211_find_vendor_ie(oui, vie->oui_type, ies,
				       ies_len);
}