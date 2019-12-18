#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_cap_info; } ;
struct ieee80211_sta_he_cap {TYPE_1__ he_cap_elem; int /*<<< orphan*/ * ppe_thres; } ;

/* Variables and functions */
 struct ieee80211_sta_he_cap* ieee80211_get_he_iftype_cap (struct ieee80211_supported_band*,scalar_t__) ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_he_mcs_nss_size (TYPE_1__*) ; 
 scalar_t__ ieee80211_he_ppe_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 ieee80211_ie_len_he_cap(struct ieee80211_sub_if_data *sdata, u8 iftype)
{
	const struct ieee80211_sta_he_cap *he_cap;
	struct ieee80211_supported_band *sband;
	u8 n;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		return 0;

	he_cap = ieee80211_get_he_iftype_cap(sband, iftype);
	if (!he_cap)
		return 0;

	n = ieee80211_he_mcs_nss_size(&he_cap->he_cap_elem);
	return 2 + 1 +
	       sizeof(he_cap->he_cap_elem) + n +
	       ieee80211_he_ppe_size(he_cap->ppe_thres[0],
				     he_cap->he_cap_elem.phy_cap_info);
}