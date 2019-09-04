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
typedef  int u32 ;
typedef  int u16 ;
struct iwl_rx_mpdu_desc {int /*<<< orphan*/  status; } ;
struct iwl_mvm {int /*<<< orphan*/  monitor_on; TYPE_1__* fw; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int FH_RSCSR_RADA_EN ; 
 int /*<<< orphan*/  IEEE80211_CCMP_HDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_CCMP_PN_LEN ; 
 int /*<<< orphan*/  IEEE80211_GCMP_PN_LEN ; 
 int /*<<< orphan*/  IEEE80211_TKIP_IV_LEN ; 
 int /*<<< orphan*/  IEEE80211_WEP_IV_LEN ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int IWL_RX_MPDU_PHY_AMPDU ; 
 int IWL_RX_MPDU_RES_STATUS_TTAK_OK ; 
 int IWL_RX_MPDU_STATUS_ICV_OK ; 
 int IWL_RX_MPDU_STATUS_MIC_OK ; 
#define  IWL_RX_MPDU_STATUS_SEC_CCM 132 
#define  IWL_RX_MPDU_STATUS_SEC_EXT_ENC 131 
#define  IWL_RX_MPDU_STATUS_SEC_GCM 130 
 int IWL_RX_MPDU_STATUS_SEC_MASK ; 
 int IWL_RX_MPDU_STATUS_SEC_NONE ; 
#define  IWL_RX_MPDU_STATUS_SEC_TKIP 129 
 int IWL_RX_MPDU_STATUS_SEC_UNKNOWN ; 
#define  IWL_RX_MPDU_STATUS_SEC_WEP 128 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_DEPRECATE_TTAK ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_ICV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MIC_STRIPPED ; 
 int /*<<< orphan*/  fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_rx_crypto(struct iwl_mvm *mvm, struct ieee80211_hdr *hdr,
			     struct ieee80211_rx_status *stats, u16 phy_info,
			     struct iwl_rx_mpdu_desc *desc,
			     u32 pkt_flags, int queue, u8 *crypt_len)
{
	u16 status = le16_to_cpu(desc->status);

	/*
	 * Drop UNKNOWN frames in aggregation, unless in monitor mode
	 * (where we don't have the keys).
	 * We limit this to aggregation because in TKIP this is a valid
	 * scenario, since we may not have the (correct) TTAK (phase 1
	 * key) in the firmware.
	 */
	if (phy_info & IWL_RX_MPDU_PHY_AMPDU &&
	    (status & IWL_RX_MPDU_STATUS_SEC_MASK) ==
	    IWL_RX_MPDU_STATUS_SEC_UNKNOWN && !mvm->monitor_on)
		return -1;

	if (!ieee80211_has_protected(hdr->frame_control) ||
	    (status & IWL_RX_MPDU_STATUS_SEC_MASK) ==
	    IWL_RX_MPDU_STATUS_SEC_NONE)
		return 0;

	/* TODO: handle packets encrypted with unknown alg */

	switch (status & IWL_RX_MPDU_STATUS_SEC_MASK) {
	case IWL_RX_MPDU_STATUS_SEC_CCM:
	case IWL_RX_MPDU_STATUS_SEC_GCM:
		BUILD_BUG_ON(IEEE80211_CCMP_PN_LEN != IEEE80211_GCMP_PN_LEN);
		/* alg is CCM: check MIC only */
		if (!(status & IWL_RX_MPDU_STATUS_MIC_OK))
			return -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		if (pkt_flags & FH_RSCSR_RADA_EN)
			stats->flag |= RX_FLAG_MIC_STRIPPED;
		*crypt_len = IEEE80211_CCMP_HDR_LEN;
		return 0;
	case IWL_RX_MPDU_STATUS_SEC_TKIP:
		/* Don't drop the frame and decrypt it in SW */
		if (!fw_has_api(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_API_DEPRECATE_TTAK) &&
		    !(status & IWL_RX_MPDU_RES_STATUS_TTAK_OK))
			return 0;

		*crypt_len = IEEE80211_TKIP_IV_LEN;
		/* fall through if TTAK OK */
	case IWL_RX_MPDU_STATUS_SEC_WEP:
		if (!(status & IWL_RX_MPDU_STATUS_ICV_OK))
			return -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		if ((status & IWL_RX_MPDU_STATUS_SEC_MASK) ==
				IWL_RX_MPDU_STATUS_SEC_WEP)
			*crypt_len = IEEE80211_WEP_IV_LEN;

		if (pkt_flags & FH_RSCSR_RADA_EN)
			stats->flag |= RX_FLAG_ICV_STRIPPED;

		return 0;
	case IWL_RX_MPDU_STATUS_SEC_EXT_ENC:
		if (!(status & IWL_RX_MPDU_STATUS_MIC_OK))
			return -1;
		stats->flag |= RX_FLAG_DECRYPTED;
		return 0;
	default:
		/* Expected in monitor (not having the keys) */
		if (!mvm->monitor_on)
			IWL_ERR(mvm, "Unhandled alg: 0x%x\n", status);
	}

	return 0;
}