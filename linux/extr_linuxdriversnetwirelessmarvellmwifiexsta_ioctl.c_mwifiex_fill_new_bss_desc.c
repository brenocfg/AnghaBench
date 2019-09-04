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
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct mwifiex_bssdescriptor {size_t beacon_buf_size; int cap_info_bitmap; int disable_11ac; int sensed_11h; int /*<<< orphan*/  bss_mode; int /*<<< orphan*/  privacy; int /*<<< orphan*/  fw_tsf; int /*<<< orphan*/  bss_band; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/ * beacon_buf; int /*<<< orphan*/  rssi; int /*<<< orphan*/  mac_address; int /*<<< orphan*/  timestamp; } ;
struct mwifiex_bss_priv {int /*<<< orphan*/  fw_tsf; int /*<<< orphan*/  band; } ;
struct cfg80211_bss_ies {size_t len; int /*<<< orphan*/  tsf; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {int capability; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  signal; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ies; scalar_t__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MWIFIEX_802_11_PRIV_FILTER_8021X_WEP ; 
 int /*<<< orphan*/  MWIFIEX_802_11_PRIV_FILTER_ACCEPT_ALL ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int WLAN_CAPABILITY_SPECTRUM_MGMT ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_update_bss_desc_with_ie (int /*<<< orphan*/ ,struct mwifiex_bssdescriptor*) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int mwifiex_fill_new_bss_desc(struct mwifiex_private *priv,
			      struct cfg80211_bss *bss,
			      struct mwifiex_bssdescriptor *bss_desc)
{
	u8 *beacon_ie;
	size_t beacon_ie_len;
	struct mwifiex_bss_priv *bss_priv = (void *)bss->priv;
	const struct cfg80211_bss_ies *ies;

	rcu_read_lock();
	ies = rcu_dereference(bss->ies);
	beacon_ie = kmemdup(ies->data, ies->len, GFP_ATOMIC);
	beacon_ie_len = ies->len;
	bss_desc->timestamp = ies->tsf;
	rcu_read_unlock();

	if (!beacon_ie) {
		mwifiex_dbg(priv->adapter, ERROR,
			    " failed to alloc beacon_ie\n");
		return -ENOMEM;
	}

	memcpy(bss_desc->mac_address, bss->bssid, ETH_ALEN);
	bss_desc->rssi = bss->signal;
	/* The caller of this function will free beacon_ie */
	bss_desc->beacon_buf = beacon_ie;
	bss_desc->beacon_buf_size = beacon_ie_len;
	bss_desc->beacon_period = bss->beacon_interval;
	bss_desc->cap_info_bitmap = bss->capability;
	bss_desc->bss_band = bss_priv->band;
	bss_desc->fw_tsf = bss_priv->fw_tsf;
	if (bss_desc->cap_info_bitmap & WLAN_CAPABILITY_PRIVACY) {
		mwifiex_dbg(priv->adapter, INFO,
			    "info: InterpretIE: AP WEP enabled\n");
		bss_desc->privacy = MWIFIEX_802_11_PRIV_FILTER_8021X_WEP;
	} else {
		bss_desc->privacy = MWIFIEX_802_11_PRIV_FILTER_ACCEPT_ALL;
	}
	if (bss_desc->cap_info_bitmap & WLAN_CAPABILITY_IBSS)
		bss_desc->bss_mode = NL80211_IFTYPE_ADHOC;
	else
		bss_desc->bss_mode = NL80211_IFTYPE_STATION;

	/* Disable 11ac by default. Enable it only where there
	 * exist VHT_CAP IE in AP beacon
	 */
	bss_desc->disable_11ac = true;

	if (bss_desc->cap_info_bitmap & WLAN_CAPABILITY_SPECTRUM_MGMT)
		bss_desc->sensed_11h = true;

	return mwifiex_update_bss_desc_with_ie(priv->adapter, bss_desc);
}