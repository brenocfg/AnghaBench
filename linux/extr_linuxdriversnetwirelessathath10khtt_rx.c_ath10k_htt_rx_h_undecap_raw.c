#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; scalar_t__ len; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {int info0; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct htt_rx_desc {TYPE_2__ msdu_end; } ;
struct ath10k {int dummy; } ;
typedef  enum htt_rx_mpdu_encrypt_type { ____Placeholder_htt_rx_mpdu_encrypt_type } htt_rx_mpdu_encrypt_type ;

/* Variables and functions */
 scalar_t__ FCS_LEN ; 
 int HTT_RX_MPDU_ENCRYPT_TKIP_WPA ; 
 scalar_t__ MICHAEL_MIC_LEN ; 
 int RX_FLAG_ICV_STRIPPED ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MIC_STRIPPED ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  RX_MSDU_END_INFO0_FIRST_MSDU ; 
 int /*<<< orphan*/  RX_MSDU_END_INFO0_LAST_MSDU ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ath10k_htt_rx_crypto_icv_len (struct ath10k*,int) ; 
 scalar_t__ ath10k_htt_rx_crypto_mic_len (struct ath10k*,int) ; 
 size_t ath10k_htt_rx_crypto_param_len (struct ath10k*,int) ; 
 int /*<<< orphan*/  ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 size_t ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_htt_rx_h_undecap_raw(struct ath10k *ar,
					struct sk_buff *msdu,
					struct ieee80211_rx_status *status,
					enum htt_rx_mpdu_encrypt_type enctype,
					bool is_decrypted)
{
	struct ieee80211_hdr *hdr;
	struct htt_rx_desc *rxd;
	size_t hdr_len;
	size_t crypto_len;
	bool is_first;
	bool is_last;

	rxd = (void *)msdu->data - sizeof(*rxd);
	is_first = !!(rxd->msdu_end.common.info0 &
		      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU));
	is_last = !!(rxd->msdu_end.common.info0 &
		     __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU));

	/* Delivered decapped frame:
	 * [802.11 header]
	 * [crypto param] <-- can be trimmed if !fcs_err &&
	 *                    !decrypt_err && !peer_idx_invalid
	 * [amsdu header] <-- only if A-MSDU
	 * [rfc1042/llc]
	 * [payload]
	 * [FCS] <-- at end, needs to be trimmed
	 */

	/* This probably shouldn't happen but warn just in case */
	if (unlikely(WARN_ON_ONCE(!is_first)))
		return;

	/* This probably shouldn't happen but warn just in case */
	if (unlikely(WARN_ON_ONCE(!(is_first && is_last))))
		return;

	skb_trim(msdu, msdu->len - FCS_LEN);

	/* In most cases this will be true for sniffed frames. It makes sense
	 * to deliver them as-is without stripping the crypto param. This is
	 * necessary for software based decryption.
	 *
	 * If there's no error then the frame is decrypted. At least that is
	 * the case for frames that come in via fragmented rx indication.
	 */
	if (!is_decrypted)
		return;

	/* The payload is decrypted so strip crypto params. Start from tail
	 * since hdr is used to compute some stuff.
	 */

	hdr = (void *)msdu->data;

	/* Tail */
	if (status->flag & RX_FLAG_IV_STRIPPED) {
		skb_trim(msdu, msdu->len -
			 ath10k_htt_rx_crypto_mic_len(ar, enctype));

		skb_trim(msdu, msdu->len -
			 ath10k_htt_rx_crypto_icv_len(ar, enctype));
	} else {
		/* MIC */
		if (status->flag & RX_FLAG_MIC_STRIPPED)
			skb_trim(msdu, msdu->len -
				 ath10k_htt_rx_crypto_mic_len(ar, enctype));

		/* ICV */
		if (status->flag & RX_FLAG_ICV_STRIPPED)
			skb_trim(msdu, msdu->len -
				 ath10k_htt_rx_crypto_icv_len(ar, enctype));
	}

	/* MMIC */
	if ((status->flag & RX_FLAG_MMIC_STRIPPED) &&
	    !ieee80211_has_morefrags(hdr->frame_control) &&
	    enctype == HTT_RX_MPDU_ENCRYPT_TKIP_WPA)
		skb_trim(msdu, msdu->len - MICHAEL_MIC_LEN);

	/* Head */
	if (status->flag & RX_FLAG_IV_STRIPPED) {
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath10k_htt_rx_crypto_param_len(ar, enctype);

		memmove((void *)msdu->data + crypto_len,
			(void *)msdu->data, hdr_len);
		skb_pull(msdu, crypto_len);
	}
}