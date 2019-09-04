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
struct mt76_txq {int send_bar; TYPE_1__* hwq; int /*<<< orphan*/  list; scalar_t__ aggr; } ;
struct mt76_dev {int dummy; } ;
struct ieee80211_txq {scalar_t__ drv_priv; } ;
struct ieee80211_sta {struct ieee80211_txq** txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ieee80211_txq**) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt76_stop_tx_queues(struct mt76_dev *dev, struct ieee80211_sta *sta,
			 bool send_bar)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sta->txq); i++) {
		struct ieee80211_txq *txq = sta->txq[i];
		struct mt76_txq *mtxq;

		if (!txq)
			continue;

		mtxq = (struct mt76_txq *)txq->drv_priv;

		spin_lock_bh(&mtxq->hwq->lock);
		mtxq->send_bar = mtxq->aggr && send_bar;
		if (!list_empty(&mtxq->list))
			list_del_init(&mtxq->list);
		spin_unlock_bh(&mtxq->hwq->lock);
	}
}