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
typedef  int u8 ;
struct mt76x2_tx_status {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x2_dev {int /*<<< orphan*/  txstatus_fifo; int /*<<< orphan*/  irq_lock; TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int /*<<< orphan*/  kfifo_is_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct mt76x2_tx_status) ; 
 int mt76x2_mac_load_tx_status (struct mt76x2_dev*,struct mt76x2_tx_status*) ; 
 int /*<<< orphan*/  mt76x2_send_tx_status (struct mt76x2_dev*,struct mt76x2_tx_status*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mac_txstat_fetch (struct mt76x2_dev*,struct mt76x2_tx_status*) ; 
 int /*<<< orphan*/  trace_mac_txstat_poll (struct mt76x2_dev*) ; 

void mt76x2_mac_poll_tx_status(struct mt76x2_dev *dev, bool irq)
{
	struct mt76x2_tx_status stat = {};
	unsigned long flags;
	u8 update = 1;
	bool ret;

	if (!test_bit(MT76_STATE_RUNNING, &dev->mt76.state))
		return;

	trace_mac_txstat_poll(dev);

	while (!irq || !kfifo_is_full(&dev->txstatus_fifo)) {
		spin_lock_irqsave(&dev->irq_lock, flags);
		ret = mt76x2_mac_load_tx_status(dev, &stat);
		spin_unlock_irqrestore(&dev->irq_lock, flags);

		if (!ret)
			break;

		trace_mac_txstat_fetch(dev, &stat);

		if (!irq) {
			mt76x2_send_tx_status(dev, &stat, &update);
			continue;
		}

		kfifo_put(&dev->txstatus_fifo, stat);
	}
}