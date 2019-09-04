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
typedef  int u32 ;
struct mwl8k_vif {int macid; int is_hw_crypto_enabled; int /*<<< orphan*/  list; int /*<<< orphan*/  bssid; scalar_t__ seqno; struct ieee80211_vif* vif; } ;
struct mwl8k_priv {int ap_macids_supported; int sta_macids_supported; int macids_used; int /*<<< orphan*/  vif_list; int /*<<< orphan*/  ap_fw; struct mwl8k_device_info* device_info; scalar_t__ sniffer_enabled; } ;
struct mwl8k_device_info {int /*<<< orphan*/  fw_image_sta; int /*<<< orphan*/  fw_image_ap; } ;
struct ieee80211_vif {int type; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct mwl8k_vif* MWL8K_VIF (struct ieee80211_vif*) ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int ffs (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mwl8k_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwl8k_cmd_set_mac_addr (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_cmd_set_new_stn_add_self (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int mwl8k_reload_firmware (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wiphy_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mwl8k_add_interface(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_vif *mwl8k_vif;
	u32 macids_supported;
	int macid, rc;
	struct mwl8k_device_info *di;

	/*
	 * Reject interface creation if sniffer mode is active, as
	 * STA operation is mutually exclusive with hardware sniffer
	 * mode.  (Sniffer mode is only used on STA firmware.)
	 */
	if (priv->sniffer_enabled) {
		wiphy_info(hw->wiphy,
			   "unable to create STA interface because sniffer mode is enabled\n");
		return -EINVAL;
	}

	di = priv->device_info;
	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		if (!priv->ap_fw && di->fw_image_ap) {
			/* we must load the ap fw to meet this request */
			if (!list_empty(&priv->vif_list))
				return -EBUSY;
			rc = mwl8k_reload_firmware(hw, di->fw_image_ap);
			if (rc)
				return rc;
		}
		macids_supported = priv->ap_macids_supported;
		break;
	case NL80211_IFTYPE_STATION:
		if (priv->ap_fw && di->fw_image_sta) {
			if (!list_empty(&priv->vif_list)) {
				wiphy_warn(hw->wiphy, "AP interface is running.\n"
					   "Adding STA interface for WDS");
			} else {
				/* we must load the sta fw to
				 * meet this request.
				 */
				rc = mwl8k_reload_firmware(hw,
							   di->fw_image_sta);
				if (rc)
					return rc;
			}
		}
		macids_supported = priv->sta_macids_supported;
		break;
	default:
		return -EINVAL;
	}

	macid = ffs(macids_supported & ~priv->macids_used);
	if (!macid--)
		return -EBUSY;

	/* Setup driver private area. */
	mwl8k_vif = MWL8K_VIF(vif);
	memset(mwl8k_vif, 0, sizeof(*mwl8k_vif));
	mwl8k_vif->vif = vif;
	mwl8k_vif->macid = macid;
	mwl8k_vif->seqno = 0;
	memcpy(mwl8k_vif->bssid, vif->addr, ETH_ALEN);
	mwl8k_vif->is_hw_crypto_enabled = false;

	/* Set the mac address.  */
	mwl8k_cmd_set_mac_addr(hw, vif, vif->addr);

	if (vif->type == NL80211_IFTYPE_AP)
		mwl8k_cmd_set_new_stn_add_self(hw, vif);

	priv->macids_used |= 1 << mwl8k_vif->macid;
	list_add_tail(&mwl8k_vif->list, &priv->vif_list);

	return 0;
}