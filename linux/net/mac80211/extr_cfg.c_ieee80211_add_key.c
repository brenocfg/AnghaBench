#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct sta_info {struct ieee80211_cipher_scheme const* cipher_scheme; } ;
struct net_device {int dummy; } ;
struct key_params {scalar_t__ mode; int cipher; int /*<<< orphan*/  seq; int /*<<< orphan*/  seq_len; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  security; } ;
struct TYPE_7__ {int /*<<< orphan*/  mfp; } ;
struct TYPE_9__ {TYPE_3__ mesh; TYPE_2__ mgd; } ;
struct TYPE_6__ {int type; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct ieee80211_key {TYPE_5__ conf; } ;
struct ieee80211_cipher_scheme {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOENT ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_NO_AUTO_TX ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_PAIRWISE ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_RX_MGMT ; 
 int /*<<< orphan*/  IEEE80211_MESH_SEC_NONE ; 
 int /*<<< orphan*/  IEEE80211_MFP_DISABLED ; 
 scalar_t__ IS_ERR (struct ieee80211_key*) ; 
#define  NL80211_IFTYPE_ADHOC 152 
#define  NL80211_IFTYPE_AP 151 
#define  NL80211_IFTYPE_AP_VLAN 150 
#define  NL80211_IFTYPE_MESH_POINT 149 
#define  NL80211_IFTYPE_MONITOR 148 
#define  NL80211_IFTYPE_NAN 147 
#define  NL80211_IFTYPE_OCB 146 
#define  NL80211_IFTYPE_P2P_CLIENT 145 
#define  NL80211_IFTYPE_P2P_DEVICE 144 
#define  NL80211_IFTYPE_P2P_GO 143 
#define  NL80211_IFTYPE_STATION 142 
#define  NL80211_IFTYPE_UNSPECIFIED 141 
#define  NL80211_IFTYPE_WDS 140 
 scalar_t__ NL80211_KEY_NO_TX ; 
 scalar_t__ NL80211_KEY_SET_TX ; 
#define  NUM_NL80211_IFTYPES 139 
 int PTR_ERR (struct ieee80211_key*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 138 
#define  WLAN_CIPHER_SUITE_BIP_CMAC_256 137 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 136 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 135 
#define  WLAN_CIPHER_SUITE_CCMP 134 
#define  WLAN_CIPHER_SUITE_CCMP_256 133 
#define  WLAN_CIPHER_SUITE_GCMP 132 
#define  WLAN_CIPHER_SUITE_GCMP_256 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  WLAN_STA_ASSOC ; 
 int /*<<< orphan*/  WLAN_STA_MFP ; 
 int fips_enabled ; 
 struct ieee80211_cipher_scheme* ieee80211_cs_get (struct ieee80211_local*,int,int) ; 
 struct ieee80211_key* ieee80211_key_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_cipher_scheme const*) ; 
 int /*<<< orphan*/  ieee80211_key_free_unused (struct ieee80211_key*) ; 
 int ieee80211_key_link (struct ieee80211_key*,struct ieee80211_sub_if_data*,struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 int ieee80211_set_tx (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_add_key(struct wiphy *wiphy, struct net_device *dev,
			     u8 key_idx, bool pairwise, const u8 *mac_addr,
			     struct key_params *params)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta = NULL;
	const struct ieee80211_cipher_scheme *cs = NULL;
	struct ieee80211_key *key;
	int err;

	if (!ieee80211_sdata_running(sdata))
		return -ENETDOWN;

	if (pairwise && params->mode == NL80211_KEY_SET_TX)
		return ieee80211_set_tx(sdata, mac_addr, key_idx);

	/* reject WEP and TKIP keys if WEP failed to initialize */
	switch (params->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_WEP104:
		if (WARN_ON_ONCE(fips_enabled))
			return -EINVAL;
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_CCMP_256:
	case WLAN_CIPHER_SUITE_AES_CMAC:
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		break;
	default:
		cs = ieee80211_cs_get(local, params->cipher, sdata->vif.type);
		break;
	}

	key = ieee80211_key_alloc(params->cipher, key_idx, params->key_len,
				  params->key, params->seq_len, params->seq,
				  cs);
	if (IS_ERR(key))
		return PTR_ERR(key);

	if (pairwise)
		key->conf.flags |= IEEE80211_KEY_FLAG_PAIRWISE;

	if (params->mode == NL80211_KEY_NO_TX)
		key->conf.flags |= IEEE80211_KEY_FLAG_NO_AUTO_TX;

	mutex_lock(&local->sta_mtx);

	if (mac_addr) {
		sta = sta_info_get_bss(sdata, mac_addr);
		/*
		 * The ASSOC test makes sure the driver is ready to
		 * receive the key. When wpa_supplicant has roamed
		 * using FT, it attempts to set the key before
		 * association has completed, this rejects that attempt
		 * so it will set the key again after association.
		 *
		 * TODO: accept the key if we have a station entry and
		 *       add it to the device after the station.
		 */
		if (!sta || !test_sta_flag(sta, WLAN_STA_ASSOC)) {
			ieee80211_key_free_unused(key);
			err = -ENOENT;
			goto out_unlock;
		}
	}

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_STATION:
		if (sdata->u.mgd.mfp != IEEE80211_MFP_DISABLED)
			key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_AP_VLAN:
		/* Keys without a station are used for TX only */
		if (sta && test_sta_flag(sta, WLAN_STA_MFP))
			key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;
		break;
	case NL80211_IFTYPE_ADHOC:
		/* no MFP (yet) */
		break;
	case NL80211_IFTYPE_MESH_POINT:
#ifdef CONFIG_MAC80211_MESH
		if (sdata->u.mesh.security != IEEE80211_MESH_SEC_NONE)
			key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;
		break;
#endif
	case NL80211_IFTYPE_WDS:
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_P2P_DEVICE:
	case NL80211_IFTYPE_NAN:
	case NL80211_IFTYPE_UNSPECIFIED:
	case NUM_NL80211_IFTYPES:
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_OCB:
		/* shouldn't happen */
		WARN_ON_ONCE(1);
		break;
	}

	if (sta)
		sta->cipher_scheme = cs;

	err = ieee80211_key_link(key, sdata, sta);

 out_unlock:
	mutex_unlock(&local->sta_mtx);

	return err;
}