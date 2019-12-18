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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct napi_struct {int dummy; } ;
struct ieee80211_supported_band {int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {size_t band; int flag; int encoding; int rate_idx; int nss; scalar_t__ rx_flags; } ;
struct ieee80211_rate {int dummy; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {int in_reconfig; int /*<<< orphan*/  started; scalar_t__ suspended; scalar_t__ quiescing; TYPE_2__ hw; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 size_t NUM_NL80211_BANDS ; 
#define  RX_ENC_HE 131 
#define  RX_ENC_HT 130 
#define  RX_ENC_LEGACY 129 
#define  RX_ENC_VHT 128 
 int RX_FLAG_FAILED_PLCP_CRC ; 
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __ieee80211_rx_handle_packet (struct ieee80211_hw*,struct ieee80211_sta*,struct sk_buff*,struct napi_struct*) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 struct sk_buff* ieee80211_rx_monitor (struct ieee80211_local*,struct sk_buff*,struct ieee80211_rate*) ; 
 int /*<<< orphan*/  ieee80211_tpt_led_trig_rx (struct ieee80211_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ softirq_count () ; 
 scalar_t__ unlikely (int) ; 

void ieee80211_rx_napi(struct ieee80211_hw *hw, struct ieee80211_sta *pubsta,
		       struct sk_buff *skb, struct napi_struct *napi)
{
	struct ieee80211_local *local = hw_to_local(hw);
	struct ieee80211_rate *rate = NULL;
	struct ieee80211_supported_band *sband;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);

	WARN_ON_ONCE(softirq_count() == 0);

	if (WARN_ON(status->band >= NUM_NL80211_BANDS))
		goto drop;

	sband = local->hw.wiphy->bands[status->band];
	if (WARN_ON(!sband))
		goto drop;

	/*
	 * If we're suspending, it is possible although not too likely
	 * that we'd be receiving frames after having already partially
	 * quiesced the stack. We can't process such frames then since
	 * that might, for example, cause stations to be added or other
	 * driver callbacks be invoked.
	 */
	if (unlikely(local->quiescing || local->suspended))
		goto drop;

	/* We might be during a HW reconfig, prevent Rx for the same reason */
	if (unlikely(local->in_reconfig))
		goto drop;

	/*
	 * The same happens when we're not even started,
	 * but that's worth a warning.
	 */
	if (WARN_ON(!local->started))
		goto drop;

	if (likely(!(status->flag & RX_FLAG_FAILED_PLCP_CRC))) {
		/*
		 * Validate the rate, unless a PLCP error means that
		 * we probably can't have a valid rate here anyway.
		 */

		switch (status->encoding) {
		case RX_ENC_HT:
			/*
			 * rate_idx is MCS index, which can be [0-76]
			 * as documented on:
			 *
			 * http://wireless.kernel.org/en/developers/Documentation/ieee80211/802.11n
			 *
			 * Anything else would be some sort of driver or
			 * hardware error. The driver should catch hardware
			 * errors.
			 */
			if (WARN(status->rate_idx > 76,
				 "Rate marked as an HT rate but passed "
				 "status->rate_idx is not "
				 "an MCS index [0-76]: %d (0x%02x)\n",
				 status->rate_idx,
				 status->rate_idx))
				goto drop;
			break;
		case RX_ENC_VHT:
			if (WARN_ONCE(status->rate_idx > 9 ||
				      !status->nss ||
				      status->nss > 8,
				      "Rate marked as a VHT rate but data is invalid: MCS: %d, NSS: %d\n",
				      status->rate_idx, status->nss))
				goto drop;
			break;
		case RX_ENC_HE:
			if (WARN_ONCE(status->rate_idx > 11 ||
				      !status->nss ||
				      status->nss > 8,
				      "Rate marked as an HE rate but data is invalid: MCS: %d, NSS: %d\n",
				      status->rate_idx, status->nss))
				goto drop;
			break;
		default:
			WARN_ON_ONCE(1);
			/* fall through */
		case RX_ENC_LEGACY:
			if (WARN_ON(status->rate_idx >= sband->n_bitrates))
				goto drop;
			rate = &sband->bitrates[status->rate_idx];
		}
	}

	status->rx_flags = 0;

	/*
	 * key references and virtual interfaces are protected using RCU
	 * and this requires that we are in a read-side RCU section during
	 * receive processing
	 */
	rcu_read_lock();

	/*
	 * Frames with failed FCS/PLCP checksum are not returned,
	 * all other frames are returned without radiotap header
	 * if it was previously present.
	 * Also, frames with less than 16 bytes are dropped.
	 */
	skb = ieee80211_rx_monitor(local, skb, rate);
	if (!skb) {
		rcu_read_unlock();
		return;
	}

	ieee80211_tpt_led_trig_rx(local,
			((struct ieee80211_hdr *)skb->data)->frame_control,
			skb->len);

	__ieee80211_rx_handle_packet(hw, pubsta, skb, napi);

	rcu_read_unlock();

	return;
 drop:
	kfree_skb(skb);
}