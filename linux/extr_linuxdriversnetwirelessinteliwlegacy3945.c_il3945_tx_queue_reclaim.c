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
struct sk_buff {int dummy; } ;
struct il_queue {int read_ptr; scalar_t__ low_mark; int /*<<< orphan*/  n_bd; } ;
struct il_tx_queue {struct il_queue q; struct sk_buff** skbs; } ;
struct il_priv {scalar_t__ mac80211_registered; TYPE_1__* ops; int /*<<< orphan*/  hw; struct il_tx_queue* txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* txq_free_tfd ) (struct il_priv*,struct il_tx_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IL39_CMD_QUEUE_NUM ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 void* il_queue_inc_wrap (int,int /*<<< orphan*/ ) ; 
 scalar_t__ il_queue_space (struct il_queue*) ; 
 int /*<<< orphan*/  il_wake_queue (struct il_priv*,struct il_tx_queue*) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*,struct il_tx_queue*) ; 

__attribute__((used)) static void
il3945_tx_queue_reclaim(struct il_priv *il, int txq_id, int idx)
{
	struct il_tx_queue *txq = &il->txq[txq_id];
	struct il_queue *q = &txq->q;
	struct sk_buff *skb;

	BUG_ON(txq_id == IL39_CMD_QUEUE_NUM);

	for (idx = il_queue_inc_wrap(idx, q->n_bd); q->read_ptr != idx;
	     q->read_ptr = il_queue_inc_wrap(q->read_ptr, q->n_bd)) {

		skb = txq->skbs[txq->q.read_ptr];
		ieee80211_tx_status_irqsafe(il->hw, skb);
		txq->skbs[txq->q.read_ptr] = NULL;
		il->ops->txq_free_tfd(il, txq);
	}

	if (il_queue_space(q) > q->low_mark && txq_id >= 0 &&
	    txq_id != IL39_CMD_QUEUE_NUM && il->mac80211_registered)
		il_wake_queue(il, txq);
}