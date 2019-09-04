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
typedef  scalar_t__ u32 ;
struct cpdma_ctlr {int /*<<< orphan*/  lock; } ;
struct cpdma_chan {scalar_t__ rate; int /*<<< orphan*/  lock; struct cpdma_ctlr* ctlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPDMA_TX_PRIO_FIXED ; 
 int /*<<< orphan*/  CPDMA_TX_RLIM ; 
 int EINVAL ; 
 int /*<<< orphan*/  _cpdma_control_set (struct cpdma_ctlr*,int /*<<< orphan*/ ,int) ; 
 int cpdma_chan_fit_rate (struct cpdma_chan*,scalar_t__,scalar_t__*,int*) ; 
 int cpdma_chan_set_factors (struct cpdma_ctlr*,struct cpdma_chan*) ; 
 int /*<<< orphan*/  is_tx_chan (struct cpdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_set_rate(struct cpdma_chan *ch, u32 rate)
{
	unsigned long flags, ch_flags;
	struct cpdma_ctlr *ctlr;
	int ret, prio_mode;
	u32 rmask;

	if (!ch || !is_tx_chan(ch))
		return -EINVAL;

	if (ch->rate == rate)
		return rate;

	ctlr = ch->ctlr;
	spin_lock_irqsave(&ctlr->lock, flags);
	spin_lock_irqsave(&ch->lock, ch_flags);

	ret = cpdma_chan_fit_rate(ch, rate, &rmask, &prio_mode);
	if (ret)
		goto err;

	ret = cpdma_chan_set_factors(ctlr, ch);
	if (ret)
		goto err;

	spin_unlock_irqrestore(&ch->lock, ch_flags);

	/* on shapers */
	_cpdma_control_set(ctlr, CPDMA_TX_RLIM, rmask);
	_cpdma_control_set(ctlr, CPDMA_TX_PRIO_FIXED, prio_mode);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	return ret;

err:
	spin_unlock_irqrestore(&ch->lock, ch_flags);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	return ret;
}