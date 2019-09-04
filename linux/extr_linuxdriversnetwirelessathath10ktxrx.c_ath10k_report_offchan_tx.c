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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ath10k {int /*<<< orphan*/  data_lock; struct sk_buff* offchan_tx_skb; int /*<<< orphan*/  offchan_tx_completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,struct sk_buff*) ; 
 scalar_t__ ath10k_mac_tx_frm_has_freq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_report_offchan_tx(struct ath10k *ar, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	if (likely(!(info->flags & IEEE80211_TX_CTL_TX_OFFCHAN)))
		return;

	if (ath10k_mac_tx_frm_has_freq(ar))
		return;

	/* If the original wait_for_completion() timed out before
	 * {data,mgmt}_tx_completed() was called then we could complete
	 * offchan_tx_completed for a different skb. Prevent this by using
	 * offchan_tx_skb.
	 */
	spin_lock_bh(&ar->data_lock);
	if (ar->offchan_tx_skb != skb) {
		ath10k_warn(ar, "completed old offchannel frame\n");
		goto out;
	}

	complete(&ar->offchan_tx_completed);
	ar->offchan_tx_skb = NULL; /* just for sanity */

	ath10k_dbg(ar, ATH10K_DBG_HTT, "completed offchannel skb %pK\n", skb);
out:
	spin_unlock_bh(&ar->data_lock);
}