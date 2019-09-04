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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
struct ath6kl_vif {size_t const* ssid; size_t ssid_len; struct ath6kl* ar; } ;
struct ath6kl {int /*<<< orphan*/  wiphy; } ;
typedef  enum network_type { ____Placeholder_network_type } network_type ;
typedef  enum ieee80211_bss_type { ____Placeholder_ieee80211_bss_type } ieee80211_bss_type ;

/* Variables and functions */
 int ADHOC_NETWORK ; 
 int /*<<< orphan*/  ATH6KL_DBG_WLAN_CFG ; 
 int /*<<< orphan*/  CFG80211_BSS_FTYPE_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_BSS_TYPE_ESS ; 
 int IEEE80211_BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_ANY ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_ESS ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_IBSS ; 
 size_t WLAN_EID_SSID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,struct ieee80211_channel*,size_t const*,size_t const*,size_t,int,int /*<<< orphan*/ ) ; 
 struct cfg80211_bss* cfg80211_inform_bss (int /*<<< orphan*/ ,struct ieee80211_channel*,int /*<<< orphan*/ ,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 size_t* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t const*,size_t) ; 

__attribute__((used)) static struct cfg80211_bss *
ath6kl_add_bss_if_needed(struct ath6kl_vif *vif,
			 enum network_type nw_type,
			 const u8 *bssid,
			 struct ieee80211_channel *chan,
			 const u8 *beacon_ie,
			 size_t beacon_ie_len)
{
	struct ath6kl *ar = vif->ar;
	struct cfg80211_bss *bss;
	u16 cap_val;
	enum ieee80211_bss_type bss_type;
	u8 *ie;

	if (nw_type & ADHOC_NETWORK) {
		cap_val = WLAN_CAPABILITY_IBSS;
		bss_type = IEEE80211_BSS_TYPE_IBSS;
	} else {
		cap_val = WLAN_CAPABILITY_ESS;
		bss_type = IEEE80211_BSS_TYPE_ESS;
	}

	bss = cfg80211_get_bss(ar->wiphy, chan, bssid,
			       vif->ssid, vif->ssid_len,
			       bss_type, IEEE80211_PRIVACY_ANY);
	if (bss == NULL) {
		/*
		 * Since cfg80211 may not yet know about the BSS,
		 * generate a partial entry until the first BSS info
		 * event becomes available.
		 *
		 * Prepend SSID element since it is not included in the Beacon
		 * IEs from the target.
		 */
		ie = kmalloc(2 + vif->ssid_len + beacon_ie_len, GFP_KERNEL);
		if (ie == NULL)
			return NULL;
		ie[0] = WLAN_EID_SSID;
		ie[1] = vif->ssid_len;
		memcpy(ie + 2, vif->ssid, vif->ssid_len);
		memcpy(ie + 2 + vif->ssid_len, beacon_ie, beacon_ie_len);
		bss = cfg80211_inform_bss(ar->wiphy, chan,
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  bssid, 0, cap_val, 100,
					  ie, 2 + vif->ssid_len + beacon_ie_len,
					  0, GFP_KERNEL);
		if (bss)
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "added bss %pM to cfg80211\n", bssid);
		kfree(ie);
	} else {
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "cfg80211 already has a bss\n");
	}

	return bss;
}