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
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_INT_TX_DONE_ALL ; 
 int MT_TXQ_MCU ; 
 int /*<<< orphan*/  mt76_queue_tx_cleanup (struct mt76x2_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x2_irq_enable (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_mac_poll_tx_status (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_mac_process_tx_status_fifo (struct mt76x2_dev*) ; 

__attribute__((used)) static void
mt76x2_tx_tasklet(unsigned long data)
{
	struct mt76x2_dev *dev = (struct mt76x2_dev *) data;
	int i;

	mt76x2_mac_process_tx_status_fifo(dev);

	for (i = MT_TXQ_MCU; i >= 0; i--)
		mt76_queue_tx_cleanup(dev, i, false);

	mt76x2_mac_poll_tx_status(dev, false);
	mt76x2_irq_enable(dev, MT_INT_TX_DONE_ALL);
}