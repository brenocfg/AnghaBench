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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct cb_pcidas_private* private; } ;
struct cb_pcidas_private {int ctrl; scalar_t__ pcibar1; } ;

/* Variables and functions */
 int PCIDAS_AI_PACER_SW ; 
 scalar_t__ PCIDAS_AI_REG ; 
 int PCIDAS_CTRL_EOAIE ; 
 int PCIDAS_CTRL_INTE ; 
 scalar_t__ PCIDAS_CTRL_REG ; 
 scalar_t__ PCIDAS_TRIG_REG ; 
 int PCIDAS_TRIG_SEL_NONE ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ai_cancel(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	struct cb_pcidas_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	/*  disable interrupts */
	devpriv->ctrl &= ~(PCIDAS_CTRL_INTE | PCIDAS_CTRL_EOAIE);
	outw(devpriv->ctrl, devpriv->pcibar1 + PCIDAS_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  disable start trigger source and burst mode */
	outw(PCIDAS_TRIG_SEL_NONE, devpriv->pcibar1 + PCIDAS_TRIG_REG);
	outw(PCIDAS_AI_PACER_SW, devpriv->pcibar1 + PCIDAS_AI_REG);

	return 0;
}