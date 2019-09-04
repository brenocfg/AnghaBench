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
struct sk_buff {int len; } ;
struct mwifiex_txinfo {int flags; int /*<<< orphan*/  aggr_num; } ;
struct mwifiex_tx_param {int next_pkt_len; } ;
struct mwifiex_adapter {int /*<<< orphan*/  tx_data_q; int /*<<< orphan*/  tx_queued; } ;

/* Variables and functions */
 int MWIFIEX_BUF_FLAG_AGGR_PKT ; 
 struct mwifiex_txinfo* MWIFIEX_SKB_TXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mwifiex_host_to_card (struct mwifiex_adapter*,struct sk_buff*,struct mwifiex_tx_param*) ; 
 int /*<<< orphan*/  mwifiex_wmm_lists_empty (struct mwifiex_adapter*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_dequeue_tx_queue(struct mwifiex_adapter *adapter)
{
	struct sk_buff *skb, *skb_next;
	struct mwifiex_txinfo *tx_info;
	struct mwifiex_tx_param tx_param;

	skb = skb_dequeue(&adapter->tx_data_q);
	if (!skb)
		return -1;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	if (tx_info->flags & MWIFIEX_BUF_FLAG_AGGR_PKT)
		atomic_sub(tx_info->aggr_num, &adapter->tx_queued);
	else
		atomic_dec(&adapter->tx_queued);

	if (!skb_queue_empty(&adapter->tx_data_q))
		skb_next = skb_peek(&adapter->tx_data_q);
	else
		skb_next = NULL;
	tx_param.next_pkt_len = ((skb_next) ? skb_next->len : 0);
	if (!tx_param.next_pkt_len) {
		if (!mwifiex_wmm_lists_empty(adapter))
			tx_param.next_pkt_len = 1;
	}
	return mwifiex_host_to_card(adapter, skb, &tx_param);
}