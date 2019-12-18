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
struct cfg80211_beacon_data {size_t tail_len; int* tail; } ;
struct cfg80211_ap_settings {void* he_cap; void* vht_cap; void* ht_cap; struct cfg80211_beacon_data beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_EXT_HE_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_EXT_SUPP_RATES ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_SUPP_RATES ; 
 int /*<<< orphan*/  WLAN_EID_VHT_CAPABILITY ; 
 int* cfg80211_find_ext_ie (int /*<<< orphan*/ ,int const*,size_t) ; 
 int* cfg80211_find_ie (int /*<<< orphan*/ ,int const*,size_t) ; 
 int /*<<< orphan*/  nl80211_check_ap_rate_selectors (struct cfg80211_ap_settings*,int const*) ; 

__attribute__((used)) static void nl80211_calculate_ap_params(struct cfg80211_ap_settings *params)
{
	const struct cfg80211_beacon_data *bcn = &params->beacon;
	size_t ies_len = bcn->tail_len;
	const u8 *ies = bcn->tail;
	const u8 *rates;
	const u8 *cap;

	rates = cfg80211_find_ie(WLAN_EID_SUPP_RATES, ies, ies_len);
	nl80211_check_ap_rate_selectors(params, rates);

	rates = cfg80211_find_ie(WLAN_EID_EXT_SUPP_RATES, ies, ies_len);
	nl80211_check_ap_rate_selectors(params, rates);

	cap = cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, ies, ies_len);
	if (cap && cap[1] >= sizeof(*params->ht_cap))
		params->ht_cap = (void *)(cap + 2);
	cap = cfg80211_find_ie(WLAN_EID_VHT_CAPABILITY, ies, ies_len);
	if (cap && cap[1] >= sizeof(*params->vht_cap))
		params->vht_cap = (void *)(cap + 2);
	cap = cfg80211_find_ext_ie(WLAN_EID_EXT_HE_CAPABILITY, ies, ies_len);
	if (cap && cap[1] >= sizeof(*params->he_cap) + 1)
		params->he_cap = (void *)(cap + 3);
}