#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int* phy_cap_info; } ;
struct ieee80211_sta_he_cap {int has_he; TYPE_2__* ppe_thres; TYPE_2__ he_cap_elem; TYPE_2__ he_mcs_nss_supp; } ;
struct TYPE_3__ {struct ieee80211_sta_he_cap he_cap; } ;
struct sta_info {TYPE_1__ sta; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_he_cap_elem {int /*<<< orphan*/  phy_cap_info; } ;

/* Variables and functions */
 int IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT ; 
 int /*<<< orphan*/  ieee80211_get_he_sta_cap (struct ieee80211_supported_band*) ; 
 int ieee80211_he_mcs_nss_size (struct ieee80211_he_cap_elem*) ; 
 int ieee80211_he_ppe_size (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int const*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_sta_he_cap*,int /*<<< orphan*/ ,int) ; 

void
ieee80211_he_cap_ie_to_sta_he_cap(struct ieee80211_sub_if_data *sdata,
				  struct ieee80211_supported_band *sband,
				  const u8 *he_cap_ie, u8 he_cap_len,
				  struct sta_info *sta)
{
	struct ieee80211_sta_he_cap *he_cap = &sta->sta.he_cap;
	struct ieee80211_he_cap_elem *he_cap_ie_elem = (void *)he_cap_ie;
	u8 he_ppe_size;
	u8 mcs_nss_size;
	u8 he_total_size;

	memset(he_cap, 0, sizeof(*he_cap));

	if (!he_cap_ie || !ieee80211_get_he_sta_cap(sband))
		return;

	/* Make sure size is OK */
	mcs_nss_size = ieee80211_he_mcs_nss_size(he_cap_ie_elem);
	he_ppe_size =
		ieee80211_he_ppe_size(he_cap_ie[sizeof(he_cap->he_cap_elem) +
						mcs_nss_size],
				      he_cap_ie_elem->phy_cap_info);
	he_total_size = sizeof(he_cap->he_cap_elem) + mcs_nss_size +
			he_ppe_size;
	if (he_cap_len < he_total_size)
		return;

	memcpy(&he_cap->he_cap_elem, he_cap_ie, sizeof(he_cap->he_cap_elem));

	/* HE Tx/Rx HE MCS NSS Support Field */
	memcpy(&he_cap->he_mcs_nss_supp,
	       &he_cap_ie[sizeof(he_cap->he_cap_elem)], mcs_nss_size);

	/* Check if there are (optional) PPE Thresholds */
	if (he_cap->he_cap_elem.phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT)
		memcpy(he_cap->ppe_thres,
		       &he_cap_ie[sizeof(he_cap->he_cap_elem) + mcs_nss_size],
		       he_ppe_size);

	he_cap->has_he = true;
}