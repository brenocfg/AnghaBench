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
typedef  int uint16_t ;
typedef  size_t u8 ;
struct TYPE_7__ {TYPE_1__* wiphy; } ;
struct mwifiex_private {scalar_t__ bss_mode; TYPE_5__* adapter; TYPE_2__ wdev; } ;
struct TYPE_9__ {int ampdu_factor; int ampdu_density; int cap; int /*<<< orphan*/  mcs; } ;
struct ieee80211_supported_band {TYPE_4__ ht_cap; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_mask; } ;
struct ieee80211_ht_cap {int ampdu_params_info; int /*<<< orphan*/  tx_BF_cap_info; void* extended_ht_cap_info; void* cap_info; TYPE_3__ mcs; } ;
struct TYPE_10__ {scalar_t__ sec_chan_offset; int /*<<< orphan*/  hw_dot_11n_dev_cap; } ;
struct TYPE_6__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ERROR ; 
 int IEEE80211_HT_AMPDU_PARM_DENSITY ; 
 int IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT ; 
 int IEEE80211_HT_AMPDU_PARM_FACTOR ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_EXT_CAP_RD_RESPONDER ; 
 scalar_t__ IEEE80211_HT_PARAM_CHA_SEC_NONE ; 
 scalar_t__ ISSUPP_BEAMFORMING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MWIFIEX_DEF_11N_TX_BF_CAP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SETHT_MCS32 (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 

int mwifiex_fill_cap_info(struct mwifiex_private *priv, u8 radio_type,
			  struct ieee80211_ht_cap *ht_cap)
{
	uint16_t ht_ext_cap = le16_to_cpu(ht_cap->extended_ht_cap_info);
	struct ieee80211_supported_band *sband =
					priv->wdev.wiphy->bands[radio_type];

	if (WARN_ON_ONCE(!sband)) {
		mwifiex_dbg(priv->adapter, ERROR, "Invalid radio type!\n");
		return -EINVAL;
	}

	ht_cap->ampdu_params_info =
		(sband->ht_cap.ampdu_factor &
		 IEEE80211_HT_AMPDU_PARM_FACTOR) |
		((sband->ht_cap.ampdu_density <<
		 IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT) &
		 IEEE80211_HT_AMPDU_PARM_DENSITY);

	memcpy((u8 *)&ht_cap->mcs, &sband->ht_cap.mcs,
	       sizeof(sband->ht_cap.mcs));

	if (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    (sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
	     (priv->adapter->sec_chan_offset !=
					IEEE80211_HT_PARAM_CHA_SEC_NONE)))
		/* Set MCS32 for infra mode or ad-hoc mode with 40MHz support */
		SETHT_MCS32(ht_cap->mcs.rx_mask);

	/* Clear RD responder bit */
	ht_ext_cap &= ~IEEE80211_HT_EXT_CAP_RD_RESPONDER;

	ht_cap->cap_info = cpu_to_le16(sband->ht_cap.cap);
	ht_cap->extended_ht_cap_info = cpu_to_le16(ht_ext_cap);

	if (ISSUPP_BEAMFORMING(priv->adapter->hw_dot_11n_dev_cap))
		ht_cap->tx_BF_cap_info = cpu_to_le32(MWIFIEX_DEF_11N_TX_BF_CAP);

	return 0;
}