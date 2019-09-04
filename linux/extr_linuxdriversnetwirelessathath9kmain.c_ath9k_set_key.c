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
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {scalar_t__ cipher; int flags; int hw_key_idx; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  mutex; TYPE_1__* sc_ah; } ;
struct ath_node {int* key_idx; } ;
struct ath_common {int dummy; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  sw_mgmt_crypto_tx; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CONFIG ; 
#define  DISABLE_KEY 129 
 int EINVAL ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_SW_MGMT_TX ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
#define  SET_KEY 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WLAN_CIPHER_SUITE_CCMP ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int /*<<< orphan*/  ath9k_del_ps_key (struct ath_softc*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 struct ath_common* ath9k_hw_common (TYPE_1__*) ; 
 scalar_t__ ath9k_modparam_nohwcrypt ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int ath_key_config (struct ath_common*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  ath_key_delete (struct ath_common*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_set_key(struct ieee80211_hw *hw,
			 enum set_key_cmd cmd,
			 struct ieee80211_vif *vif,
			 struct ieee80211_sta *sta,
			 struct ieee80211_key_conf *key)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_node *an = NULL;
	int ret = 0, i;

	if (ath9k_modparam_nohwcrypt)
		return -ENOSPC;

	if ((vif->type == NL80211_IFTYPE_ADHOC ||
	     vif->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) {
		/*
		 * For now, disable hw crypto for the RSN IBSS group keys. This
		 * could be optimized in the future to use a modified key cache
		 * design to support per-STA RX GTK, but until that gets
		 * implemented, use of software crypto for group addressed
		 * frames is a acceptable to allow RSN IBSS to be used.
		 */
		return -EOPNOTSUPP;
	}

	mutex_lock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	ath_dbg(common, CONFIG, "Set HW Key %d\n", cmd);
	if (sta)
		an = (struct ath_node *)sta->drv_priv;

	switch (cmd) {
	case SET_KEY:
		if (sta)
			ath9k_del_ps_key(sc, vif, sta);

		key->hw_key_idx = 0;
		ret = ath_key_config(common, vif, sta, key);
		if (ret >= 0) {
			key->hw_key_idx = ret;
			/* push IV and Michael MIC generation to stack */
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			if (key->cipher == WLAN_CIPHER_SUITE_TKIP)
				key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			if (sc->sc_ah->sw_mgmt_crypto_tx &&
			    key->cipher == WLAN_CIPHER_SUITE_CCMP)
				key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
			ret = 0;
		}
		if (an && key->hw_key_idx) {
			for (i = 0; i < ARRAY_SIZE(an->key_idx); i++) {
				if (an->key_idx[i])
					continue;
				an->key_idx[i] = key->hw_key_idx;
				break;
			}
			WARN_ON(i == ARRAY_SIZE(an->key_idx));
		}
		break;
	case DISABLE_KEY:
		ath_key_delete(common, key);
		if (an) {
			for (i = 0; i < ARRAY_SIZE(an->key_idx); i++) {
				if (an->key_idx[i] != key->hw_key_idx)
					continue;
				an->key_idx[i] = 0;
				break;
			}
		}
		key->hw_key_idx = 0;
		break;
	default:
		ret = -EINVAL;
	}

	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);

	return ret;
}