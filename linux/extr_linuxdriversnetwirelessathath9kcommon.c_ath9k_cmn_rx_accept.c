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
typedef  int u8 ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
struct ath_rx_status {scalar_t__ rs_keyix; int rs_status; } ;
struct ath_hw {scalar_t__ is_monitoring; } ;
struct ath_common {int /*<<< orphan*/  ccmp_keymap; int /*<<< orphan*/  tkip_keymap; struct ath_hw* ah; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ATH9K_RXERR_CRC ; 
 int ATH9K_RXERR_DECRYPT ; 
 int ATH9K_RXERR_KEYMISS ; 
 int ATH9K_RXERR_MIC ; 
 scalar_t__ ATH9K_RXKEYIX_INVALID ; 
 unsigned int FIF_FCSFAIL ; 
 int IEEE80211_SCTL_FRAG ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_ERROR ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

bool ath9k_cmn_rx_accept(struct ath_common *common,
			 struct ieee80211_hdr *hdr,
			 struct ieee80211_rx_status *rxs,
			 struct ath_rx_status *rx_stats,
			 bool *decrypt_error,
			 unsigned int rxfilter)
{
	struct ath_hw *ah = common->ah;
	bool is_mc, is_valid_tkip, strip_mic, mic_error;
	__le16 fc;

	fc = hdr->frame_control;

	is_mc = !!is_multicast_ether_addr(hdr->addr1);
	is_valid_tkip = rx_stats->rs_keyix != ATH9K_RXKEYIX_INVALID &&
		test_bit(rx_stats->rs_keyix, common->tkip_keymap);
	strip_mic = is_valid_tkip && ieee80211_is_data(fc) &&
		ieee80211_has_protected(fc) &&
		!(rx_stats->rs_status &
		(ATH9K_RXERR_DECRYPT | ATH9K_RXERR_CRC | ATH9K_RXERR_MIC |
		 ATH9K_RXERR_KEYMISS));

	/*
	 * Key miss events are only relevant for pairwise keys where the
	 * descriptor does contain a valid key index. This has been observed
	 * mostly with CCMP encryption.
	 */
	if (rx_stats->rs_keyix == ATH9K_RXKEYIX_INVALID ||
	    !test_bit(rx_stats->rs_keyix, common->ccmp_keymap))
		rx_stats->rs_status &= ~ATH9K_RXERR_KEYMISS;

	mic_error = is_valid_tkip && !ieee80211_is_ctl(fc) &&
		!ieee80211_has_morefrags(fc) &&
		!(le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_FRAG) &&
		(rx_stats->rs_status & ATH9K_RXERR_MIC);

	/*
	 * The rx_stats->rs_status will not be set until the end of the
	 * chained descriptors so it can be ignored if rs_more is set. The
	 * rs_more will be false at the last element of the chained
	 * descriptors.
	 */
	if (rx_stats->rs_status != 0) {
		u8 status_mask;

		if (rx_stats->rs_status & ATH9K_RXERR_CRC) {
			rxs->flag |= RX_FLAG_FAILED_FCS_CRC;
			mic_error = false;
		}

		if ((rx_stats->rs_status & ATH9K_RXERR_DECRYPT) ||
		    (!is_mc && (rx_stats->rs_status & ATH9K_RXERR_KEYMISS))) {
			*decrypt_error = true;
			mic_error = false;
		}


		/*
		 * Reject error frames with the exception of
		 * decryption and MIC failures. For monitor mode,
		 * we also ignore the CRC error.
		 */
		status_mask = ATH9K_RXERR_DECRYPT | ATH9K_RXERR_MIC |
			      ATH9K_RXERR_KEYMISS;

		if (ah->is_monitoring && (rxfilter & FIF_FCSFAIL))
			status_mask |= ATH9K_RXERR_CRC;

		if (rx_stats->rs_status & ~status_mask)
			return false;
	}

	/*
	 * For unicast frames the MIC error bit can have false positives,
	 * so all MIC error reports need to be validated in software.
	 * False negatives are not common, so skip software verification
	 * if the hardware considers the MIC valid.
	 */
	if (strip_mic)
		rxs->flag |= RX_FLAG_MMIC_STRIPPED;
	else if (is_mc && mic_error)
		rxs->flag |= RX_FLAG_MMIC_ERROR;

	return true;
}