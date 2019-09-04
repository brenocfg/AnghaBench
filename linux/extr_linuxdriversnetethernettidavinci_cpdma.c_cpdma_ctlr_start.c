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
struct TYPE_2__ {scalar_t__ rxcp; scalar_t__ txcp; scalar_t__ rxhdp; scalar_t__ txhdp; scalar_t__ has_soft_reset; } ;
struct cpdma_ctlr {scalar_t__ state; int num_chan; int /*<<< orphan*/  lock; struct cpdma_chan** channels; TYPE_1__ params; } ;
struct cpdma_chan {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cpdma_chan**) ; 
 int /*<<< orphan*/  CPDMA_RXCONTROL ; 
 int /*<<< orphan*/  CPDMA_RXINTMASKCLEAR ; 
 int /*<<< orphan*/  CPDMA_RX_BUFFER_OFFSET ; 
 int /*<<< orphan*/  CPDMA_SOFTRESET ; 
 scalar_t__ CPDMA_STATE_ACTIVE ; 
 scalar_t__ CPDMA_STATE_IDLE ; 
 int /*<<< orphan*/  CPDMA_TXCONTROL ; 
 int /*<<< orphan*/  CPDMA_TXINTMASKCLEAR ; 
 int /*<<< orphan*/  CPDMA_TX_PRIO_FIXED ; 
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _cpdma_control_set (struct cpdma_ctlr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpdma_chan_on (struct cpdma_chan*) ; 
 int /*<<< orphan*/  cpdma_chan_set_chan_shaper (struct cpdma_chan*) ; 
 scalar_t__ dma_reg_read (struct cpdma_ctlr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_reg_write (struct cpdma_ctlr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_tx_chan (struct cpdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int cpdma_ctlr_start(struct cpdma_ctlr *ctlr)
{
	struct cpdma_chan *chan;
	unsigned long flags;
	int i, prio_mode;

	spin_lock_irqsave(&ctlr->lock, flags);
	if (ctlr->state != CPDMA_STATE_IDLE) {
		spin_unlock_irqrestore(&ctlr->lock, flags);
		return -EBUSY;
	}

	if (ctlr->params.has_soft_reset) {
		unsigned timeout = 10 * 100;

		dma_reg_write(ctlr, CPDMA_SOFTRESET, 1);
		while (timeout) {
			if (dma_reg_read(ctlr, CPDMA_SOFTRESET) == 0)
				break;
			udelay(10);
			timeout--;
		}
		WARN_ON(!timeout);
	}

	for (i = 0; i < ctlr->num_chan; i++) {
		writel(0, ctlr->params.txhdp + 4 * i);
		writel(0, ctlr->params.rxhdp + 4 * i);
		writel(0, ctlr->params.txcp + 4 * i);
		writel(0, ctlr->params.rxcp + 4 * i);
	}

	dma_reg_write(ctlr, CPDMA_RXINTMASKCLEAR, 0xffffffff);
	dma_reg_write(ctlr, CPDMA_TXINTMASKCLEAR, 0xffffffff);

	dma_reg_write(ctlr, CPDMA_TXCONTROL, 1);
	dma_reg_write(ctlr, CPDMA_RXCONTROL, 1);

	ctlr->state = CPDMA_STATE_ACTIVE;

	prio_mode = 0;
	for (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) {
		chan = ctlr->channels[i];
		if (chan) {
			cpdma_chan_set_chan_shaper(chan);
			cpdma_chan_on(chan);

			/* off prio mode if all tx channels are rate limited */
			if (is_tx_chan(chan) && !chan->rate)
				prio_mode = 1;
		}
	}

	_cpdma_control_set(ctlr, CPDMA_TX_PRIO_FIXED, prio_mode);
	_cpdma_control_set(ctlr, CPDMA_RX_BUFFER_OFFSET, 0);

	spin_unlock_irqrestore(&ctlr->lock, flags);
	return 0;
}