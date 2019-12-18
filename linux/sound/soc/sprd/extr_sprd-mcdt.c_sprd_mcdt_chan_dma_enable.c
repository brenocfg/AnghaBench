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
typedef  int /*<<< orphan*/  u32 ;
struct sprd_mcdt_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct sprd_mcdt_chan {int dma_enable; int type; int /*<<< orphan*/  id; scalar_t__ int_enable; struct sprd_mcdt_dev* mcdt; } ;
typedef  enum sprd_mcdt_dma_chan { ____Placeholder_sprd_mcdt_dma_chan } sprd_mcdt_dma_chan ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MCDT_FIFO_LENGTH ; 
#define  SPRD_MCDT_ADC_CHAN 129 
#define  SPRD_MCDT_DAC_CHAN 128 
 int SPRD_MCDT_DMA_CH4 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_dma_ack_select (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_dma_chn_select (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_dma_enable (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_fifo_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_set_watermark (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_dma_ack_select (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_dma_chn_select (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_dma_enable (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_fifo_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_set_watermark (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sprd_mcdt_chan_dma_enable(struct sprd_mcdt_chan *chan,
			      enum sprd_mcdt_dma_chan dma_chan,
			      u32 water_mark)
{
	struct sprd_mcdt_dev *mcdt = chan->mcdt;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&mcdt->lock, flags);

	if (chan->dma_enable || chan->int_enable ||
	    dma_chan > SPRD_MCDT_DMA_CH4) {
		dev_err(mcdt->dev, "Failed to set DMA mode\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		return -EINVAL;
	}

	switch (chan->type) {
	case SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_adc_fifo_clear(mcdt, chan->id);
		sprd_mcdt_adc_set_watermark(mcdt, chan->id,
					    water_mark, MCDT_FIFO_LENGTH - 1);
		sprd_mcdt_adc_dma_enable(mcdt, chan->id, true);
		sprd_mcdt_adc_dma_chn_select(mcdt, chan->id, dma_chan);
		sprd_mcdt_adc_dma_ack_select(mcdt, chan->id, dma_chan);
		break;

	case SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_dac_fifo_clear(mcdt, chan->id);
		sprd_mcdt_dac_set_watermark(mcdt, chan->id,
					    MCDT_FIFO_LENGTH - 1, water_mark);
		sprd_mcdt_dac_dma_enable(mcdt, chan->id, true);
		sprd_mcdt_dac_dma_chn_select(mcdt, chan->id, dma_chan);
		sprd_mcdt_dac_dma_ack_select(mcdt, chan->id, dma_chan);
		break;

	default:
		dev_err(mcdt->dev, "Unsupported channel type\n");
		ret = -EINVAL;
	}

	if (!ret)
		chan->dma_enable = true;

	spin_unlock_irqrestore(&mcdt->lock, flags);

	return ret;
}