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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * phy_cap_info; int /*<<< orphan*/ * mac_cap_info; } ;
struct ieee80211_sta_he_cap {int /*<<< orphan*/ * ppe_thres; int /*<<< orphan*/  he_mcs_nss_supp; TYPE_1__ he_cap_elem; scalar_t__ has_he; } ;
struct ieee80211_sband_iftype_data {int /*<<< orphan*/  types_mask; struct ieee80211_sta_he_cap he_cap; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  NL80211_BAND_IFTYPE_ATTR_HE_CAP_MAC ; 
 int /*<<< orphan*/  NL80211_BAND_IFTYPE_ATTR_HE_CAP_MCS_SET ; 
 int /*<<< orphan*/  NL80211_BAND_IFTYPE_ATTR_HE_CAP_PHY ; 
 int /*<<< orphan*/  NL80211_BAND_IFTYPE_ATTR_HE_CAP_PPE ; 
 int /*<<< orphan*/  NL80211_BAND_IFTYPE_ATTR_IFTYPES ; 
 scalar_t__ nl80211_put_iftypes (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nl80211_send_iftype_data(struct sk_buff *msg,
			 const struct ieee80211_sband_iftype_data *iftdata)
{
	const struct ieee80211_sta_he_cap *he_cap = &iftdata->he_cap;

	if (nl80211_put_iftypes(msg, NL80211_BAND_IFTYPE_ATTR_IFTYPES,
				iftdata->types_mask))
		return -ENOBUFS;

	if (he_cap->has_he) {
		if (nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_MAC,
			    sizeof(he_cap->he_cap_elem.mac_cap_info),
			    he_cap->he_cap_elem.mac_cap_info) ||
		    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_PHY,
			    sizeof(he_cap->he_cap_elem.phy_cap_info),
			    he_cap->he_cap_elem.phy_cap_info) ||
		    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_MCS_SET,
			    sizeof(he_cap->he_mcs_nss_supp),
			    &he_cap->he_mcs_nss_supp) ||
		    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_PPE,
			    sizeof(he_cap->ppe_thres), he_cap->ppe_thres))
			return -ENOBUFS;
	}

	return 0;
}