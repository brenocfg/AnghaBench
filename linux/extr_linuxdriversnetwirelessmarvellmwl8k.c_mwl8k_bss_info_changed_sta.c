#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mwl8k_priv {int capture_beacon; int /*<<< orphan*/ * capture_bssid; int /*<<< orphan*/  ap_fw; } ;
struct TYPE_14__ {int /*<<< orphan*/  bssid; scalar_t__ assoc; int /*<<< orphan*/  use_short_slot; int /*<<< orphan*/  use_short_preamble; int /*<<< orphan*/  basic_rates; } ;
struct ieee80211_vif {TYPE_6__ bss_conf; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_10__ {TYPE_1__ mcs; } ;
struct ieee80211_sta {int* supp_rates; TYPE_2__ ht_cap; } ;
struct TYPE_12__ {TYPE_3__* chan; } ;
struct TYPE_13__ {TYPE_4__ chandef; } ;
struct ieee80211_hw {TYPE_5__ conf; struct mwl8k_priv* priv; } ;
struct ieee80211_bss_conf {int dummy; } ;
struct TYPE_16__ {int hw_value; } ;
struct TYPE_15__ {int hw_value; } ;
struct TYPE_11__ {size_t band; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_HT ; 
 int ETH_ALEN ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int ffs (int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mwl8k_cmd_set_aid (struct ieee80211_hw*,struct ieee80211_vif*,int) ; 
 int mwl8k_cmd_set_rate (struct ieee80211_hw*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int mwl8k_cmd_set_slot (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_cmd_use_fixed_rate_ap (struct ieee80211_hw*,int,int) ; 
 int mwl8k_cmd_use_fixed_rate_sta (struct ieee80211_hw*) ; 
 scalar_t__ mwl8k_fw_lock (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_fw_unlock (struct ieee80211_hw*) ; 
 TYPE_8__* mwl8k_rates_24 ; 
 TYPE_7__* mwl8k_rates_50 ; 
 int mwl8k_set_radio_preamble (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void
mwl8k_bss_info_changed_sta(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			   struct ieee80211_bss_conf *info, u32 changed)
{
	struct mwl8k_priv *priv = hw->priv;
	u32 ap_legacy_rates = 0;
	u8 ap_mcs_rates[16];
	int rc;

	if (mwl8k_fw_lock(hw))
		return;

	/*
	 * No need to capture a beacon if we're no longer associated.
	 */
	if ((changed & BSS_CHANGED_ASSOC) && !vif->bss_conf.assoc)
		priv->capture_beacon = false;

	/*
	 * Get the AP's legacy and MCS rates.
	 */
	if (vif->bss_conf.assoc) {
		struct ieee80211_sta *ap;

		rcu_read_lock();

		ap = ieee80211_find_sta(vif, vif->bss_conf.bssid);
		if (ap == NULL) {
			rcu_read_unlock();
			goto out;
		}

		if (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ) {
			ap_legacy_rates = ap->supp_rates[NL80211_BAND_2GHZ];
		} else {
			ap_legacy_rates =
				ap->supp_rates[NL80211_BAND_5GHZ] << 5;
		}
		memcpy(ap_mcs_rates, ap->ht_cap.mcs.rx_mask, 16);

		rcu_read_unlock();

		if (changed & BSS_CHANGED_ASSOC) {
			if (!priv->ap_fw) {
				rc = mwl8k_cmd_set_rate(hw, vif,
							ap_legacy_rates,
							ap_mcs_rates);
				if (rc)
					goto out;

				rc = mwl8k_cmd_use_fixed_rate_sta(hw);
				if (rc)
					goto out;
			} else {
				int idx;
				int rate;

				/* Use AP firmware specific rate command.
				 */
				idx = ffs(vif->bss_conf.basic_rates);
				if (idx)
					idx--;

				if (hw->conf.chandef.chan->band ==
				    NL80211_BAND_2GHZ)
					rate = mwl8k_rates_24[idx].hw_value;
				else
					rate = mwl8k_rates_50[idx].hw_value;

				mwl8k_cmd_use_fixed_rate_ap(hw, rate, rate);
			}
		}
	}

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		rc = mwl8k_set_radio_preamble(hw,
				vif->bss_conf.use_short_preamble);
		if (rc)
			goto out;
	}

	if ((changed & BSS_CHANGED_ERP_SLOT) && !priv->ap_fw)  {
		rc = mwl8k_cmd_set_slot(hw, vif->bss_conf.use_short_slot);
		if (rc)
			goto out;
	}

	if (vif->bss_conf.assoc && !priv->ap_fw &&
	    (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_ERP_CTS_PROT |
			BSS_CHANGED_HT))) {
		rc = mwl8k_cmd_set_aid(hw, vif, ap_legacy_rates);
		if (rc)
			goto out;
	}

	if (vif->bss_conf.assoc &&
	    (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BEACON_INT))) {
		/*
		 * Finalize the join.  Tell rx handler to process
		 * next beacon from our BSSID.
		 */
		memcpy(priv->capture_bssid, vif->bss_conf.bssid, ETH_ALEN);
		priv->capture_beacon = true;
	}

out:
	mwl8k_fw_unlock(hw);
}