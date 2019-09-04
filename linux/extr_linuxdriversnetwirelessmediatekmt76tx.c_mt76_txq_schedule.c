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
struct mt76_queue {int swq_queued; int /*<<< orphan*/  swq; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int mt76_txq_schedule_list (struct mt76_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void mt76_txq_schedule(struct mt76_dev *dev, struct mt76_queue *hwq)
{
	int len;

	rcu_read_lock();
	do {
		if (hwq->swq_queued >= 4 || list_empty(&hwq->swq))
			break;

		len = mt76_txq_schedule_list(dev, hwq);
	} while (len > 0);
	rcu_read_unlock();
}