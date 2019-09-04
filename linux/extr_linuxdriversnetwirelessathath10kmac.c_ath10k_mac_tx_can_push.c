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
struct ieee80211_txq {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ath10k_txq {scalar_t__ num_fw_queued; scalar_t__ num_push_allowed; } ;
struct TYPE_3__ {scalar_t__ mode; scalar_t__ num_push_allowed; } ;
struct TYPE_4__ {scalar_t__ num_pending_tx; TYPE_1__ tx_q_state; } ;
struct ath10k {TYPE_2__ htt; } ;

/* Variables and functions */
 scalar_t__ HTT_TX_MODE_SWITCH_PUSH ; 

__attribute__((used)) static bool ath10k_mac_tx_can_push(struct ieee80211_hw *hw,
				   struct ieee80211_txq *txq)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_txq *artxq = (void *)txq->drv_priv;

	/* No need to get locks */

	if (ar->htt.tx_q_state.mode == HTT_TX_MODE_SWITCH_PUSH)
		return true;

	if (ar->htt.num_pending_tx < ar->htt.tx_q_state.num_push_allowed)
		return true;

	if (artxq->num_fw_queued < artxq->num_push_allowed)
		return true;

	return false;
}