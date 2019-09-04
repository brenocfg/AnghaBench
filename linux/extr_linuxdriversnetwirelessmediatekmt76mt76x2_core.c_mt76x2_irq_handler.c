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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dfs_tasklet; } ;
struct TYPE_3__ {int /*<<< orphan*/ * q_tx; int /*<<< orphan*/ * napi; int /*<<< orphan*/  state; } ;
struct mt76x2_dev {int irqmask; TYPE_2__ dfs_pd; int /*<<< orphan*/  tx_tasklet; TYPE_1__ mt76; int /*<<< orphan*/  pre_tbtt_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int MT_INT_GPTIMER ; 
 int MT_INT_PRE_TBTT ; 
 int MT_INT_RX_DONE (int) ; 
 int /*<<< orphan*/  MT_INT_SOURCE_CSR ; 
 int MT_INT_TBTT ; 
 int MT_INT_TX_DONE_ALL ; 
 int MT_INT_TX_STAT ; 
 size_t MT_TXQ_PSD ; 
 int /*<<< orphan*/  mt76_queue_kick (struct mt76x2_dev*,int /*<<< orphan*/ *) ; 
 int mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_irq_disable (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_mac_poll_tx_status (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dev_irq (struct mt76x2_dev*,int,int) ; 

irqreturn_t mt76x2_irq_handler(int irq, void *dev_instance)
{
	struct mt76x2_dev *dev = dev_instance;
	u32 intr;

	intr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	mt76_wr(dev, MT_INT_SOURCE_CSR, intr);

	if (!test_bit(MT76_STATE_INITIALIZED, &dev->mt76.state))
		return IRQ_NONE;

	trace_dev_irq(dev, intr, dev->irqmask);

	intr &= dev->irqmask;

	if (intr & MT_INT_TX_DONE_ALL) {
		mt76x2_irq_disable(dev, MT_INT_TX_DONE_ALL);
		tasklet_schedule(&dev->tx_tasklet);
	}

	if (intr & MT_INT_RX_DONE(0)) {
		mt76x2_irq_disable(dev, MT_INT_RX_DONE(0));
		napi_schedule(&dev->mt76.napi[0]);
	}

	if (intr & MT_INT_RX_DONE(1)) {
		mt76x2_irq_disable(dev, MT_INT_RX_DONE(1));
		napi_schedule(&dev->mt76.napi[1]);
	}

	if (intr & MT_INT_PRE_TBTT)
		tasklet_schedule(&dev->pre_tbtt_tasklet);

	/* send buffered multicast frames now */
	if (intr & MT_INT_TBTT)
		mt76_queue_kick(dev, &dev->mt76.q_tx[MT_TXQ_PSD]);

	if (intr & MT_INT_TX_STAT) {
		mt76x2_mac_poll_tx_status(dev, true);
		tasklet_schedule(&dev->tx_tasklet);
	}

	if (intr & MT_INT_GPTIMER) {
		mt76x2_irq_disable(dev, MT_INT_GPTIMER);
		tasklet_schedule(&dev->dfs_pd.dfs_tasklet);
	}

	return IRQ_HANDLED;
}