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
struct sprd_mcdt_dev {int /*<<< orphan*/  lock; } ;
struct sprd_mcdt_chan {int dma_enable; int type; int /*<<< orphan*/  id; struct sprd_mcdt_dev* mcdt; } ;

/* Variables and functions */
#define  SPRD_MCDT_ADC_CHAN 129 
#define  SPRD_MCDT_DAC_CHAN 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_dma_enable (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_fifo_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_dma_enable (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_fifo_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 

void sprd_mcdt_chan_dma_disable(struct sprd_mcdt_chan *chan)
{
	struct sprd_mcdt_dev *mcdt = chan->mcdt;
	unsigned long flags;

	spin_lock_irqsave(&mcdt->lock, flags);

	if (!chan->dma_enable) {
		spin_unlock_irqrestore(&mcdt->lock, flags);
		return;
	}

	switch (chan->type) {
	case SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_adc_dma_enable(mcdt, chan->id, false);
		sprd_mcdt_adc_fifo_clear(mcdt, chan->id);
		break;

	case SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_dac_dma_enable(mcdt, chan->id, false);
		sprd_mcdt_dac_fifo_clear(mcdt, chan->id);
		break;

	default:
		break;
	}

	chan->dma_enable = false;
	spin_unlock_irqrestore(&mcdt->lock, flags);
}