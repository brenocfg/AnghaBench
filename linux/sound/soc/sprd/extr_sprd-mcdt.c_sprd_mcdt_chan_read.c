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
typedef  int u32 ;
struct sprd_mcdt_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct sprd_mcdt_chan {int /*<<< orphan*/  id; scalar_t__ dma_enable; struct sprd_mcdt_dev* mcdt; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MCDT_ADC_FIFO_REAL_EMPTY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sprd_mcdt_adc_fifo_avail (struct sprd_mcdt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_adc_read_fifo (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sprd_mcdt_chan_fifo_sts (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sprd_mcdt_chan_read(struct sprd_mcdt_chan *chan, char *rx_buf, u32 size)
{
	struct sprd_mcdt_dev *mcdt = chan->mcdt;
	unsigned long flags;
	int i = 0, avail, words = size / 4;
	u32 *buf = (u32 *)rx_buf;

	spin_lock_irqsave(&mcdt->lock, flags);

	if (chan->dma_enable) {
		dev_err(mcdt->dev, "Can not read data when DMA mode enabled\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		return -EINVAL;
	}

	if (sprd_mcdt_chan_fifo_sts(mcdt, chan->id, MCDT_ADC_FIFO_REAL_EMPTY)) {
		dev_err(mcdt->dev, "Channel fifo is empty\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		return -EBUSY;
	}

	avail = sprd_mcdt_adc_fifo_avail(mcdt, chan->id);
	if (size > avail)
		words = avail / 4;

	while (i++ < words)
		sprd_mcdt_adc_read_fifo(mcdt, chan->id, buf++);

	spin_unlock_irqrestore(&mcdt->lock, flags);
	return words * 4;
}