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
struct cb_pcidas_private {int ctrl; int ao_ctrl; scalar_t__ pcibar1; } ;

/* Variables and functions */
 int PCIDAS_AO_DACEN ; 
 int PCIDAS_AO_PACER_MASK ; 
 scalar_t__ PCIDAS_AO_REG ; 
 int PCIDAS_CTRL_DAEMIE ; 
 int PCIDAS_CTRL_DAHFIE ; 
 scalar_t__ PCIDAS_CTRL_REG ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ao_cancel(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	struct cb_pcidas_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	/*  disable interrupts */
	devpriv->ctrl &= ~(PCIDAS_CTRL_DAHFIE | PCIDAS_CTRL_DAEMIE);
	outw(devpriv->ctrl, devpriv->pcibar1 + PCIDAS_CTRL_REG);

	/*  disable output */
	devpriv->ao_ctrl &= ~(PCIDAS_AO_DACEN | PCIDAS_AO_PACER_MASK);
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return 0;
}