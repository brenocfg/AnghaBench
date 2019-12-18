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
struct sprd_mcdt_dev {int /*<<< orphan*/  lock; struct sprd_mcdt_chan* chan; } ;
struct sprd_mcdt_chan {TYPE_1__* cb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* notify ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MCDT_ADC_CHANNEL_NUM ; 
 int /*<<< orphan*/  MCDT_ADC_FIFO_AF_INT ; 
 int MCDT_DAC_CHANNEL_NUM ; 
 int /*<<< orphan*/  MCDT_DAC_FIFO_AE_INT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_mcdt_chan_int_clear (struct sprd_mcdt_dev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sprd_mcdt_chan_int_sts (struct sprd_mcdt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sprd_mcdt_irq_handler(int irq, void *dev_id)
{
	struct sprd_mcdt_dev *mcdt = (struct sprd_mcdt_dev *)dev_id;
	int i;

	spin_lock(&mcdt->lock);

	for (i = 0; i < MCDT_ADC_CHANNEL_NUM; i++) {
		if (sprd_mcdt_chan_int_sts(mcdt, i, MCDT_ADC_FIFO_AF_INT)) {
			struct sprd_mcdt_chan *chan = &mcdt->chan[i];

			sprd_mcdt_chan_int_clear(mcdt, i, MCDT_ADC_FIFO_AF_INT);
			if (chan->cb)
				chan->cb->notify(chan->cb->data);
		}
	}

	for (i = 0; i < MCDT_DAC_CHANNEL_NUM; i++) {
		if (sprd_mcdt_chan_int_sts(mcdt, i, MCDT_DAC_FIFO_AE_INT)) {
			struct sprd_mcdt_chan *chan =
				&mcdt->chan[i + MCDT_ADC_CHANNEL_NUM];

			sprd_mcdt_chan_int_clear(mcdt, i, MCDT_DAC_FIFO_AE_INT);
			if (chan->cb)
				chan->cb->notify(chan->cb->data);
		}
	}

	spin_unlock(&mcdt->lock);

	return IRQ_HANDLED;
}