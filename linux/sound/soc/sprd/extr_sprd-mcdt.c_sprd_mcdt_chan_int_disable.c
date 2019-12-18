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
struct sprd_mcdt_chan {int int_enable; int type; int /*<<< orphan*/  id; struct sprd_mcdt_dev* mcdt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCDT_ADC_FIFO_AF_INT ; 
 int /*<<< orphan*/  MCDT_DAC_FIFO_AE_INT ; 
#define  SPRD_MCDT_ADC_CHAN 129 
#define  SPRD_MCDT_DAC_CHAN 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_mcdt_ap_int_enable (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprd_mcdt_chan_int_clear (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_mcdt_chan_int_en (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void sprd_mcdt_chan_int_disable(struct sprd_mcdt_chan *chan)
{
	struct sprd_mcdt_dev *mcdt = chan->mcdt;
	unsigned long flags;

	spin_lock_irqsave(&mcdt->lock, flags);

	if (!chan->int_enable) {
		spin_unlock_irqrestore(&mcdt->lock, flags);
		return;
	}

	switch (chan->type) {
	case SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_ADC_FIFO_AF_INT, false);
		sprd_mcdt_chan_int_clear(mcdt, chan->id, MCDT_ADC_FIFO_AF_INT);
		sprd_mcdt_ap_int_enable(mcdt, chan->id, false);
		break;

	case SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_DAC_FIFO_AE_INT, false);
		sprd_mcdt_chan_int_clear(mcdt, chan->id, MCDT_DAC_FIFO_AE_INT);
		sprd_mcdt_ap_int_enable(mcdt, chan->id, false);
		break;

	default:
		break;
	}

	chan->int_enable = false;
	spin_unlock_irqrestore(&mcdt->lock, flags);
}