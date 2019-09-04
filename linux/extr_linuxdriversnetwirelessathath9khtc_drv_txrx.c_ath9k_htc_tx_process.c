#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_rate {int count; int idx; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {struct ieee80211_tx_rate* rates; } ;
struct TYPE_7__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {int flags; TYPE_5__ status; TYPE_1__ control; } ;
struct TYPE_9__ {TYPE_2__* chan; } ;
struct ieee80211_conf {TYPE_3__ chandef; } ;
struct ath9k_htc_tx_ctl {int txok; } ;
struct TYPE_10__ {scalar_t__ queued_cnt; int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {TYPE_6__* hw; TYPE_4__ tx; } ;
struct __wmi_event_txstatus {int ts_flags; int /*<<< orphan*/  ts_rate; } ;
struct TYPE_12__ {struct ieee80211_conf conf; } ;
struct TYPE_8__ {scalar_t__ band; } ;

/* Variables and functions */
 int ATH9K_HTC_TXSTAT_ACK ; 
 int ATH9K_HTC_TXSTAT_CW40 ; 
 int ATH9K_HTC_TXSTAT_FILT ; 
 int ATH9K_HTC_TXSTAT_MCS ; 
 int /*<<< orphan*/  ATH9K_HTC_TXSTAT_RATE ; 
 int ATH9K_HTC_TXSTAT_RTC_CTS ; 
 int ATH9K_HTC_TXSTAT_SGI ; 
 struct ath9k_htc_tx_ctl* HTC_SKB_CB (struct sk_buff*) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_USE_RTS_CTS ; 
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_AMPDU ; 
 int IEEE80211_TX_STAT_TX_FILTERED ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath9k_htc_check_tx_aggr (struct ath9k_htc_priv*,struct ieee80211_vif*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath9k_htc_tx_clear_slot (struct ath9k_htc_priv*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (TYPE_6__*,struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int strip_drv_header (struct ath9k_htc_priv*,struct sk_buff*) ; 

__attribute__((used)) static void ath9k_htc_tx_process(struct ath9k_htc_priv *priv,
				 struct sk_buff *skb,
				 struct __wmi_event_txstatus *txs)
{
	struct ieee80211_vif *vif;
	struct ath9k_htc_tx_ctl *tx_ctl;
	struct ieee80211_tx_info *tx_info;
	struct ieee80211_tx_rate *rate;
	struct ieee80211_conf *cur_conf = &priv->hw->conf;
	bool txok;
	int slot;
	int hdrlen, padsize;

	slot = strip_drv_header(priv, skb);
	if (slot < 0) {
		dev_kfree_skb_any(skb);
		return;
	}

	tx_ctl = HTC_SKB_CB(skb);
	txok = tx_ctl->txok;
	tx_info = IEEE80211_SKB_CB(skb);
	vif = tx_info->control.vif;
	rate = &tx_info->status.rates[0];

	memset(&tx_info->status, 0, sizeof(tx_info->status));

	/*
	 * URB submission failed for this frame, it never reached
	 * the target.
	 */
	if (!txok || !vif || !txs)
		goto send_mac80211;

	if (txs->ts_flags & ATH9K_HTC_TXSTAT_ACK) {
		tx_info->flags |= IEEE80211_TX_STAT_ACK;
		if (tx_info->flags & IEEE80211_TX_CTL_AMPDU)
			tx_info->flags |= IEEE80211_TX_STAT_AMPDU;
	}

	if (txs->ts_flags & ATH9K_HTC_TXSTAT_FILT)
		tx_info->flags |= IEEE80211_TX_STAT_TX_FILTERED;

	if (txs->ts_flags & ATH9K_HTC_TXSTAT_RTC_CTS)
		rate->flags |= IEEE80211_TX_RC_USE_RTS_CTS;

	rate->count = 1;
	rate->idx = MS(txs->ts_rate, ATH9K_HTC_TXSTAT_RATE);

	if (txs->ts_flags & ATH9K_HTC_TXSTAT_MCS) {
		rate->flags |= IEEE80211_TX_RC_MCS;

		if (txs->ts_flags & ATH9K_HTC_TXSTAT_CW40)
			rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		if (txs->ts_flags & ATH9K_HTC_TXSTAT_SGI)
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;
	} else {
		if (cur_conf->chandef.chan->band == NL80211_BAND_5GHZ)
			rate->idx += 4; /* No CCK rates */
	}

	ath9k_htc_check_tx_aggr(priv, vif, skb);

send_mac80211:
	spin_lock_bh(&priv->tx.tx_lock);
	if (WARN_ON(--priv->tx.queued_cnt < 0))
		priv->tx.queued_cnt = 0;
	spin_unlock_bh(&priv->tx.tx_lock);

	ath9k_htc_tx_clear_slot(priv, slot);

	/* Remove padding before handing frame back to mac80211 */
	hdrlen = ieee80211_get_hdrlen_from_skb(skb);

	padsize = hdrlen & 3;
	if (padsize && skb->len > hdrlen + padsize) {
		memmove(skb->data + padsize, skb->data, hdrlen);
		skb_pull(skb, padsize);
	}

	/* Send status to mac80211 */
	ieee80211_tx_status(priv->hw, skb);
}