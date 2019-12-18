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
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_tx_data {TYPE_1__* local; int /*<<< orphan*/  skbs; int /*<<< orphan*/ * skb; } ;
typedef  scalar_t__ ieee80211_tx_result ;
struct TYPE_2__ {int /*<<< orphan*/  tx_handlers_queued; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_handlers_drop; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_TXH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_RATE_CONTROL ; 
 int /*<<< orphan*/  I802_DEBUG_INC (int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ *) ; 
 int IEEE80211_TX_INTFL_RETRANSMISSION ; 
 scalar_t__ TX_CONTINUE ; 
 scalar_t__ TX_DROP ; 
 scalar_t__ TX_QUEUED ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_purge_tx_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_tx_h_calculate_duration ; 
 int /*<<< orphan*/  ieee80211_tx_h_encrypt ; 
 int /*<<< orphan*/  ieee80211_tx_h_fragment ; 
 int /*<<< orphan*/  ieee80211_tx_h_michael_mic_add ; 
 int /*<<< orphan*/  ieee80211_tx_h_sequence ; 
 int /*<<< orphan*/  ieee80211_tx_h_stats ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int invoke_tx_handlers_late(struct ieee80211_tx_data *tx)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	ieee80211_tx_result res = TX_CONTINUE;

	if (unlikely(info->flags & IEEE80211_TX_INTFL_RETRANSMISSION)) {
		__skb_queue_tail(&tx->skbs, tx->skb);
		tx->skb = NULL;
		goto txh_done;
	}

	CALL_TXH(ieee80211_tx_h_michael_mic_add);
	CALL_TXH(ieee80211_tx_h_sequence);
	CALL_TXH(ieee80211_tx_h_fragment);
	/* handlers after fragment must be aware of tx info fragmentation! */
	CALL_TXH(ieee80211_tx_h_stats);
	CALL_TXH(ieee80211_tx_h_encrypt);
	if (!ieee80211_hw_check(&tx->local->hw, HAS_RATE_CONTROL))
		CALL_TXH(ieee80211_tx_h_calculate_duration);
#undef CALL_TXH

 txh_done:
	if (unlikely(res == TX_DROP)) {
		I802_DEBUG_INC(tx->local->tx_handlers_drop);
		if (tx->skb)
			ieee80211_free_txskb(&tx->local->hw, tx->skb);
		else
			ieee80211_purge_tx_queue(&tx->local->hw, &tx->skbs);
		return -1;
	} else if (unlikely(res == TX_QUEUED)) {
		I802_DEBUG_INC(tx->local->tx_handlers_queued);
		return -1;
	}

	return 0;
}