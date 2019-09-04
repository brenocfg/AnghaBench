#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {size_t priority; } ;
struct netdev_queue {int dummy; } ;
struct mwifiex_private {TYPE_1__* adapter; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * wmm_tx_pending; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  bypass_tx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 scalar_t__ MAX_TX_PENDING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int* mwifiex_1d_to_wmm_queue ; 
 scalar_t__ mwifiex_bypass_tx_queue (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mwifiex_queue_main_work (TYPE_1__*) ; 
 int /*<<< orphan*/  mwifiex_wmm_add_buf_bypass_txqueue (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_wmm_add_buf_txqueue (struct mwifiex_private*,struct sk_buff*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 

int mwifiex_queue_tx_pkt(struct mwifiex_private *priv, struct sk_buff *skb)
{
	struct netdev_queue *txq;
	int index = mwifiex_1d_to_wmm_queue[skb->priority];

	if (atomic_inc_return(&priv->wmm_tx_pending[index]) >= MAX_TX_PENDING) {
		txq = netdev_get_tx_queue(priv->netdev, index);
		if (!netif_tx_queue_stopped(txq)) {
			netif_tx_stop_queue(txq);
			mwifiex_dbg(priv->adapter, DATA,
				    "stop queue: %d\n", index);
		}
	}

	if (mwifiex_bypass_tx_queue(priv, skb)) {
		atomic_inc(&priv->adapter->tx_pending);
		atomic_inc(&priv->adapter->bypass_tx_pending);
		mwifiex_wmm_add_buf_bypass_txqueue(priv, skb);
	 } else {
		atomic_inc(&priv->adapter->tx_pending);
		mwifiex_wmm_add_buf_txqueue(priv, skb);
	 }

	mwifiex_queue_main_work(priv->adapter);

	return 0;
}