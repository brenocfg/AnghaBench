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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct iwl_tx_cmd {int sec_ctl; int /*<<< orphan*/ * key; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_key_conf {int cipher; int keyidx; int /*<<< orphan*/  hw_key_idx; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; int /*<<< orphan*/  tx_pn; } ;
typedef  enum iwl_tx_cmd_sec_ctrl { ____Placeholder_iwl_tx_cmd_sec_ctrl } iwl_tx_cmd_sec_ctrl ;

/* Variables and functions */
 int TX_CMD_SEC_CCM ; 
 int TX_CMD_SEC_EXT ; 
 int TX_CMD_SEC_GCMP ; 
 int TX_CMD_SEC_KEY128 ; 
 int TX_CMD_SEC_KEY_FROM_TABLE ; 
 int TX_CMD_SEC_TKIP ; 
 int TX_CMD_SEC_WEP ; 
 int TX_CMD_SEC_WEP_KEY_IDX_MSK ; 
 int TX_CMD_SEC_WEP_KEY_IDX_POS ; 
#define  WLAN_CIPHER_SUITE_CCMP 134 
#define  WLAN_CIPHER_SUITE_CCMP_256 133 
#define  WLAN_CIPHER_SUITE_GCMP 132 
#define  WLAN_CIPHER_SUITE_GCMP_256 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_get_tkip_p2k (struct ieee80211_key_conf*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_tkip_add_iv (int /*<<< orphan*/ *,struct ieee80211_key_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_set_tx_cmd_ccmp (struct ieee80211_tx_info*,struct iwl_tx_cmd*) ; 
 int /*<<< orphan*/  iwl_mvm_set_tx_cmd_pn (struct ieee80211_tx_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_set_tx_cmd_crypto(struct iwl_mvm *mvm,
				      struct ieee80211_tx_info *info,
				      struct iwl_tx_cmd *tx_cmd,
				      struct sk_buff *skb_frag,
				      int hdrlen)
{
	struct ieee80211_key_conf *keyconf = info->control.hw_key;
	u8 *crypto_hdr = skb_frag->data + hdrlen;
	enum iwl_tx_cmd_sec_ctrl type = TX_CMD_SEC_CCM;
	u64 pn;

	switch (keyconf->cipher) {
	case WLAN_CIPHER_SUITE_CCMP:
		iwl_mvm_set_tx_cmd_ccmp(info, tx_cmd);
		iwl_mvm_set_tx_cmd_pn(info, crypto_hdr);
		break;

	case WLAN_CIPHER_SUITE_TKIP:
		tx_cmd->sec_ctl = TX_CMD_SEC_TKIP;
		pn = atomic64_inc_return(&keyconf->tx_pn);
		ieee80211_tkip_add_iv(crypto_hdr, keyconf, pn);
		ieee80211_get_tkip_p2k(keyconf, skb_frag, tx_cmd->key);
		break;

	case WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		/* fall through */
	case WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |= TX_CMD_SEC_WEP |
			((keyconf->keyidx << TX_CMD_SEC_WEP_KEY_IDX_POS) &
			  TX_CMD_SEC_WEP_KEY_IDX_MSK);

		memcpy(&tx_cmd->key[3], keyconf->key, keyconf->keylen);
		break;
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		type = TX_CMD_SEC_GCMP;
		/* Fall through */
	case WLAN_CIPHER_SUITE_CCMP_256:
		/* TODO: Taking the key from the table might introduce a race
		 * when PTK rekeying is done, having an old packets with a PN
		 * based on the old key but the message encrypted with a new
		 * one.
		 * Need to handle this.
		 */
		tx_cmd->sec_ctl |= type | TX_CMD_SEC_KEY_FROM_TABLE;
		tx_cmd->key[0] = keyconf->hw_key_idx;
		iwl_mvm_set_tx_cmd_pn(info, crypto_hdr);
		break;
	default:
		tx_cmd->sec_ctl |= TX_CMD_SEC_EXT;
	}
}