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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct htt_rx_offload_msdu {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  msdu_len; } ;
struct ath10k_htt {struct ieee80211_rx_status rx_status; } ;
struct ath10k {struct ath10k_htt htt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_FLAG_NO_SIGNAL_VAL ; 
 size_t __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ath10k_htt_rx_h_channel (struct ath10k*,struct ieee80211_rx_status*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_htt_rx_h_queue_msdu (struct ath10k*,struct ieee80211_rx_status*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_htt_rx_h_rx_offload_prot (struct ieee80211_rx_status*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 size_t skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static void ath10k_htt_rx_h_rx_offload(struct ath10k *ar,
				       struct sk_buff_head *list)
{
	struct ath10k_htt *htt = &ar->htt;
	struct ieee80211_rx_status *status = &htt->rx_status;
	struct htt_rx_offload_msdu *rx;
	struct sk_buff *msdu;
	size_t offset;

	while ((msdu = __skb_dequeue(list))) {
		/* Offloaded frames don't have Rx descriptor. Instead they have
		 * a short meta information header.
		 */

		rx = (void *)msdu->data;

		skb_put(msdu, sizeof(*rx));
		skb_pull(msdu, sizeof(*rx));

		if (skb_tailroom(msdu) < __le16_to_cpu(rx->msdu_len)) {
			ath10k_warn(ar, "dropping frame: offloaded rx msdu is too long!\n");
			dev_kfree_skb_any(msdu);
			continue;
		}

		skb_put(msdu, __le16_to_cpu(rx->msdu_len));

		/* Offloaded rx header length isn't multiple of 2 nor 4 so the
		 * actual payload is unaligned. Align the frame.  Otherwise
		 * mac80211 complains.  This shouldn't reduce performance much
		 * because these offloaded frames are rare.
		 */
		offset = 4 - ((unsigned long)msdu->data & 3);
		skb_put(msdu, offset);
		memmove(msdu->data + offset, msdu->data, msdu->len);
		skb_pull(msdu, offset);

		/* FIXME: The frame is NWifi. Re-construct QoS Control
		 * if possible later.
		 */

		memset(status, 0, sizeof(*status));
		status->flag |= RX_FLAG_NO_SIGNAL_VAL;

		ath10k_htt_rx_h_rx_offload_prot(status, msdu);
		ath10k_htt_rx_h_channel(ar, status, NULL, rx->vdev_id);
		ath10k_htt_rx_h_queue_msdu(ar, status, msdu);
	}
}