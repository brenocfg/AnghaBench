#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wsm_remove_key {int index; } ;
struct TYPE_19__ {int /*<<< orphan*/  keyid; int /*<<< orphan*/  mic_key; int /*<<< orphan*/  keydata; } ;
struct TYPE_18__ {int /*<<< orphan*/  keyid; int /*<<< orphan*/  mic_key; int /*<<< orphan*/  keydata; int /*<<< orphan*/  peer; } ;
struct TYPE_17__ {int /*<<< orphan*/  keyid; int /*<<< orphan*/ * rx_seqnum; int /*<<< orphan*/  keydata; } ;
struct TYPE_15__ {int /*<<< orphan*/  keydata; int /*<<< orphan*/  peer; } ;
struct TYPE_14__ {int* rx_seqnum; int /*<<< orphan*/  keyid; int /*<<< orphan*/  rx_mic_key; int /*<<< orphan*/  keydata; } ;
struct TYPE_12__ {int /*<<< orphan*/  rx_mic_key; int /*<<< orphan*/  tx_mic_key; int /*<<< orphan*/  keydata; int /*<<< orphan*/  peer; } ;
struct TYPE_11__ {int keylen; int /*<<< orphan*/  keyid; int /*<<< orphan*/  keydata; } ;
struct TYPE_20__ {int keylen; int /*<<< orphan*/  keydata; int /*<<< orphan*/  peer; } ;
struct wsm_add_key {TYPE_8__ wapi_group; int /*<<< orphan*/  type; TYPE_7__ wapi_pairwise; TYPE_6__ aes_group; TYPE_4__ aes_pairwise; TYPE_3__ tkip_group; TYPE_1__ tkip_pairwise; TYPE_10__ wep_group; TYPE_9__ wep_pairwise; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/ * addr; } ;
struct TYPE_16__ {int /*<<< orphan*/ * pn; } ;
struct TYPE_13__ {int iv16; int iv32; } ;
struct ieee80211_key_seq {TYPE_5__ ccmp; TYPE_2__ tkip; } ;
struct ieee80211_key_conf {int flags; int cipher; int keylen; int hw_key_idx; int /*<<< orphan*/  keyidx; int /*<<< orphan*/ * key; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_common {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  mode; struct wsm_add_key* keys; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int DISABLE_KEY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 int IEEE80211_KEY_FLAG_RESERVE_TAILROOM ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int SET_KEY ; 
#define  WLAN_CIPHER_SUITE_CCMP 132 
#define  WLAN_CIPHER_SUITE_SMS4 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int WSM_KEY_MAX_INDEX ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_AES_GROUP ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_AES_PAIRWISE ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_TKIP_GROUP ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_TKIP_PAIRWISE ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_WAPI_GROUP ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_WAPI_PAIRWISE ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_WEP_DEFAULT ; 
 int /*<<< orphan*/  WSM_KEY_TYPE_WEP_PAIRWISE ; 
 int cw1200_alloc_key (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_free_key (struct cw1200_common*,int) ; 
 int /*<<< orphan*/  ieee80211_get_key_rx_seq (struct ieee80211_key_conf*,int /*<<< orphan*/ ,struct ieee80211_key_seq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int wsm_add_key (struct cw1200_common*,struct wsm_add_key*) ; 
 int wsm_remove_key (struct cw1200_common*,struct wsm_remove_key*) ; 

int cw1200_set_key(struct ieee80211_hw *dev, enum set_key_cmd cmd,
		   struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		   struct ieee80211_key_conf *key)
{
	int ret = -EOPNOTSUPP;
	struct cw1200_common *priv = dev->priv;
	struct ieee80211_key_seq seq;

	mutex_lock(&priv->conf_mutex);

	if (cmd == SET_KEY) {
		u8 *peer_addr = NULL;
		int pairwise = (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) ?
			1 : 0;
		int idx = cw1200_alloc_key(priv);
		struct wsm_add_key *wsm_key = &priv->keys[idx];

		if (idx < 0) {
			ret = -EINVAL;
			goto finally;
		}

		if (sta)
			peer_addr = sta->addr;

		key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE |
			      IEEE80211_KEY_FLAG_RESERVE_TAILROOM;

		switch (key->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			if (key->keylen > 16) {
				cw1200_free_key(priv, idx);
				ret = -EINVAL;
				goto finally;
			}

			if (pairwise) {
				wsm_key->type = WSM_KEY_TYPE_WEP_PAIRWISE;
				memcpy(wsm_key->wep_pairwise.peer,
				       peer_addr, ETH_ALEN);
				memcpy(wsm_key->wep_pairwise.keydata,
				       &key->key[0], key->keylen);
				wsm_key->wep_pairwise.keylen = key->keylen;
			} else {
				wsm_key->type = WSM_KEY_TYPE_WEP_DEFAULT;
				memcpy(wsm_key->wep_group.keydata,
				       &key->key[0], key->keylen);
				wsm_key->wep_group.keylen = key->keylen;
				wsm_key->wep_group.keyid = key->keyidx;
			}
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			ieee80211_get_key_rx_seq(key, 0, &seq);
			if (pairwise) {
				wsm_key->type = WSM_KEY_TYPE_TKIP_PAIRWISE;
				memcpy(wsm_key->tkip_pairwise.peer,
				       peer_addr, ETH_ALEN);
				memcpy(wsm_key->tkip_pairwise.keydata,
				       &key->key[0], 16);
				memcpy(wsm_key->tkip_pairwise.tx_mic_key,
				       &key->key[16], 8);
				memcpy(wsm_key->tkip_pairwise.rx_mic_key,
				       &key->key[24], 8);
			} else {
				size_t mic_offset =
					(priv->mode == NL80211_IFTYPE_AP) ?
					16 : 24;
				wsm_key->type = WSM_KEY_TYPE_TKIP_GROUP;
				memcpy(wsm_key->tkip_group.keydata,
				       &key->key[0], 16);
				memcpy(wsm_key->tkip_group.rx_mic_key,
				       &key->key[mic_offset], 8);

				wsm_key->tkip_group.rx_seqnum[0] = seq.tkip.iv16 & 0xff;
				wsm_key->tkip_group.rx_seqnum[1] = (seq.tkip.iv16 >> 8) & 0xff;
				wsm_key->tkip_group.rx_seqnum[2] = seq.tkip.iv32 & 0xff;
				wsm_key->tkip_group.rx_seqnum[3] = (seq.tkip.iv32 >> 8) & 0xff;
				wsm_key->tkip_group.rx_seqnum[4] = (seq.tkip.iv32 >> 16) & 0xff;
				wsm_key->tkip_group.rx_seqnum[5] = (seq.tkip.iv32 >> 24) & 0xff;
				wsm_key->tkip_group.rx_seqnum[6] = 0;
				wsm_key->tkip_group.rx_seqnum[7] = 0;

				wsm_key->tkip_group.keyid = key->keyidx;
			}
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			ieee80211_get_key_rx_seq(key, 0, &seq);
			if (pairwise) {
				wsm_key->type = WSM_KEY_TYPE_AES_PAIRWISE;
				memcpy(wsm_key->aes_pairwise.peer,
				       peer_addr, ETH_ALEN);
				memcpy(wsm_key->aes_pairwise.keydata,
				       &key->key[0], 16);
			} else {
				wsm_key->type = WSM_KEY_TYPE_AES_GROUP;
				memcpy(wsm_key->aes_group.keydata,
				       &key->key[0], 16);

				wsm_key->aes_group.rx_seqnum[0] = seq.ccmp.pn[5];
				wsm_key->aes_group.rx_seqnum[1] = seq.ccmp.pn[4];
				wsm_key->aes_group.rx_seqnum[2] = seq.ccmp.pn[3];
				wsm_key->aes_group.rx_seqnum[3] = seq.ccmp.pn[2];
				wsm_key->aes_group.rx_seqnum[4] = seq.ccmp.pn[1];
				wsm_key->aes_group.rx_seqnum[5] = seq.ccmp.pn[0];
				wsm_key->aes_group.rx_seqnum[6] = 0;
				wsm_key->aes_group.rx_seqnum[7] = 0;
				wsm_key->aes_group.keyid = key->keyidx;
			}
			break;
		case WLAN_CIPHER_SUITE_SMS4:
			if (pairwise) {
				wsm_key->type = WSM_KEY_TYPE_WAPI_PAIRWISE;
				memcpy(wsm_key->wapi_pairwise.peer,
				       peer_addr, ETH_ALEN);
				memcpy(wsm_key->wapi_pairwise.keydata,
				       &key->key[0], 16);
				memcpy(wsm_key->wapi_pairwise.mic_key,
				       &key->key[16], 16);
				wsm_key->wapi_pairwise.keyid = key->keyidx;
			} else {
				wsm_key->type = WSM_KEY_TYPE_WAPI_GROUP;
				memcpy(wsm_key->wapi_group.keydata,
				       &key->key[0],  16);
				memcpy(wsm_key->wapi_group.mic_key,
				       &key->key[16], 16);
				wsm_key->wapi_group.keyid = key->keyidx;
			}
			break;
		default:
			pr_warn("Unhandled key type %d\n", key->cipher);
			cw1200_free_key(priv, idx);
			ret = -EOPNOTSUPP;
			goto finally;
		}
		ret = wsm_add_key(priv, wsm_key);
		if (!ret)
			key->hw_key_idx = idx;
		else
			cw1200_free_key(priv, idx);
	} else if (cmd == DISABLE_KEY) {
		struct wsm_remove_key wsm_key = {
			.index = key->hw_key_idx,
		};

		if (wsm_key.index > WSM_KEY_MAX_INDEX) {
			ret = -EINVAL;
			goto finally;
		}

		cw1200_free_key(priv, wsm_key.index);
		ret = wsm_remove_key(priv, &wsm_key);
	} else {
		pr_warn("Unhandled key command %d\n", cmd);
	}

finally:
	mutex_unlock(&priv->conf_mutex);
	return ret;
}