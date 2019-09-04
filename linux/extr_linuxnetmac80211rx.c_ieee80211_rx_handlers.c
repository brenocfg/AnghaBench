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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_rx_data {TYPE_1__* local; struct sk_buff* skb; } ;
typedef  scalar_t__ ieee80211_rx_result ;
struct TYPE_2__ {int /*<<< orphan*/  rx_path_lock; } ;

/* Variables and functions */
 scalar_t__ RX_CONTINUE ; 
 scalar_t__ RX_DROP_MONITOR ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 scalar_t__ ieee80211_rx_h_action (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_action_return (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_amsdu (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_check_more_data (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_ctrl (struct ieee80211_rx_data*,struct sk_buff_head*) ; 
 scalar_t__ ieee80211_rx_h_data (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_decrypt (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_defragment (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_mgmt (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_mgmt_check (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_michael_mic_verify (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_sta_process (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_uapsd_and_pspoll (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_userspace_mgmt (struct ieee80211_rx_data*) ; 
 int /*<<< orphan*/  ieee80211_rx_handlers_result (struct ieee80211_rx_data*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_rx_handlers(struct ieee80211_rx_data *rx,
				  struct sk_buff_head *frames)
{
	ieee80211_rx_result res = RX_DROP_MONITOR;
	struct sk_buff *skb;

#define CALL_RXH(rxh)			\
	do {				\
		res = rxh(rx);		\
		if (res != RX_CONTINUE)	\
			goto rxh_next;  \
	} while (0)

	/* Lock here to avoid hitting all of the data used in the RX
	 * path (e.g. key data, station data, ...) concurrently when
	 * a frame is released from the reorder buffer due to timeout
	 * from the timer, potentially concurrently with RX from the
	 * driver.
	 */
	spin_lock_bh(&rx->local->rx_path_lock);

	while ((skb = __skb_dequeue(frames))) {
		/*
		 * all the other fields are valid across frames
		 * that belong to an aMPDU since they are on the
		 * same TID from the same station
		 */
		rx->skb = skb;

		CALL_RXH(ieee80211_rx_h_check_more_data);
		CALL_RXH(ieee80211_rx_h_uapsd_and_pspoll);
		CALL_RXH(ieee80211_rx_h_sta_process);
		CALL_RXH(ieee80211_rx_h_decrypt);
		CALL_RXH(ieee80211_rx_h_defragment);
		CALL_RXH(ieee80211_rx_h_michael_mic_verify);
		/* must be after MMIC verify so header is counted in MPDU mic */
#ifdef CONFIG_MAC80211_MESH
		if (ieee80211_vif_is_mesh(&rx->sdata->vif))
			CALL_RXH(ieee80211_rx_h_mesh_fwding);
#endif
		CALL_RXH(ieee80211_rx_h_amsdu);
		CALL_RXH(ieee80211_rx_h_data);

		/* special treatment -- needs the queue */
		res = ieee80211_rx_h_ctrl(rx, frames);
		if (res != RX_CONTINUE)
			goto rxh_next;

		CALL_RXH(ieee80211_rx_h_mgmt_check);
		CALL_RXH(ieee80211_rx_h_action);
		CALL_RXH(ieee80211_rx_h_userspace_mgmt);
		CALL_RXH(ieee80211_rx_h_action_return);
		CALL_RXH(ieee80211_rx_h_mgmt);

 rxh_next:
		ieee80211_rx_handlers_result(rx, res);

#undef CALL_RXH
	}

	spin_unlock_bh(&rx->local->rx_path_lock);
}