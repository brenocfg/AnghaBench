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
struct ieee80211_tx_data {TYPE_1__* local; int /*<<< orphan*/  skbs; scalar_t__ skb; } ;
typedef  scalar_t__ ieee80211_tx_result ;
struct TYPE_2__ {int /*<<< orphan*/  tx_handlers_queued; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_handlers_drop; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_RATE_CONTROL ; 
 int /*<<< orphan*/  I802_DEBUG_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ TX_CONTINUE ; 
 scalar_t__ TX_DROP ; 
 scalar_t__ TX_QUEUED ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_purge_tx_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_tx_h_check_assoc (struct ieee80211_tx_data*) ; 
 scalar_t__ ieee80211_tx_h_check_control_port_protocol (struct ieee80211_tx_data*) ; 
 scalar_t__ ieee80211_tx_h_dynamic_ps (struct ieee80211_tx_data*) ; 
 scalar_t__ ieee80211_tx_h_ps_buf (struct ieee80211_tx_data*) ; 
 scalar_t__ ieee80211_tx_h_rate_ctrl (struct ieee80211_tx_data*) ; 
 scalar_t__ ieee80211_tx_h_select_key (struct ieee80211_tx_data*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int invoke_tx_handlers_early(struct ieee80211_tx_data *tx)
{
	ieee80211_tx_result res = TX_DROP;

#define CALL_TXH(txh) \
	do {				\
		res = txh(tx);		\
		if (res != TX_CONTINUE)	\
			goto txh_done;	\
	} while (0)

	CALL_TXH(ieee80211_tx_h_dynamic_ps);
	CALL_TXH(ieee80211_tx_h_check_assoc);
	CALL_TXH(ieee80211_tx_h_ps_buf);
	CALL_TXH(ieee80211_tx_h_check_control_port_protocol);
	CALL_TXH(ieee80211_tx_h_select_key);
	if (!ieee80211_hw_check(&tx->local->hw, HAS_RATE_CONTROL))
		CALL_TXH(ieee80211_tx_h_rate_ctrl);

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