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
struct sprd_mcdt_chan_callback {int dummy; } ;
struct sprd_mcdt_chan {int int_enable; int type; struct sprd_mcdt_chan_callback* cb; int /*<<< orphan*/  id; scalar_t__ dma_enable; struct sprd_mcdt_dev* mcdt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MCDT_ADC_FIFO_AF_INT ; 
 int /*<<< orphan*/  MCDT_DAC_FIFO_AE_INT ; 
 int /*<<< orphan*/  MCDT_FIFO_LENGTH ; 
#define  SPRD_MCDT_ADC_CHAN 129 
#define  SPRD_MCDT_DAC_CHAN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_fifo_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_set_watermark (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_ap_int_enable (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_chan_int_en (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_fifo_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_dac_set_watermark (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sprd_mcdt_chan_int_enable(struct sprd_mcdt_chan *chan, u32 water_mark,
			      struct sprd_mcdt_chan_callback *cb)
{
	struct sprd_mcdt_dev *mcdt = chan->mcdt;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&mcdt->lock, flags);

	if (chan->dma_enable || chan->int_enable) {
		dev_err(mcdt->dev, "Failed to set interrupt mode.\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		return -EINVAL;
	}

	switch (chan->type) {
	case SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_adc_fifo_clear(mcdt, chan->id);
		sprd_mcdt_adc_set_watermark(mcdt, chan->id, water_mark,
					    MCDT_FIFO_LENGTH - 1);
		sprd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_ADC_FIFO_AF_INT, true);
		sprd_mcdt_ap_int_enable(mcdt, chan->id, true);
		break;

	case SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_dac_fifo_clear(mcdt, chan->id);
		sprd_mcdt_dac_set_watermark(mcdt, chan->id,
					    MCDT_FIFO_LENGTH - 1, water_mark);
		sprd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_DAC_FIFO_AE_INT, true);
		sprd_mcdt_ap_int_enable(mcdt, chan->id, true);
		break;

	default:
		dev_err(mcdt->dev, "Unsupported channel type\n");
		ret = -EINVAL;
	}

	if (!ret) {
		chan->cb = cb;
		chan->int_enable = true;
	}

	spin_unlock_irqrestore(&mcdt->lock, flags);

	return ret;
}