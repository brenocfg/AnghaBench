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
struct cpdma_ctlr {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int _cpdma_control_set (struct cpdma_ctlr*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_control_set(struct cpdma_ctlr *ctlr, int control, int value)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	ret = _cpdma_control_set(ctlr, control, value);
	spin_unlock_irqrestore(&ctlr->lock, flags);

	return ret;
}