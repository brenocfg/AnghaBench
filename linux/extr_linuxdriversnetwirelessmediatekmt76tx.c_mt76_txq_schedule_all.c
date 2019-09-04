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
struct mt76_queue {int /*<<< orphan*/  lock; } ;
struct mt76_dev {struct mt76_queue* q_tx; } ;

/* Variables and functions */
 int MT_TXQ_BK ; 
 int /*<<< orphan*/  mt76_txq_schedule (struct mt76_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt76_txq_schedule_all(struct mt76_dev *dev)
{
	int i;

	for (i = 0; i <= MT_TXQ_BK; i++) {
		struct mt76_queue *q = &dev->q_tx[i];

		spin_lock_bh(&q->lock);
		mt76_txq_schedule(dev, q);
		spin_unlock_bh(&q->lock);
	}
}