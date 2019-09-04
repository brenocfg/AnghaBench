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
struct pci230_private {int adccon; scalar_t__ hwver; int /*<<< orphan*/  ai_stop_spinlock; int /*<<< orphan*/  ai_cmd_started; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  pacer; struct pci230_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I8254_MODE0 ; 
 int /*<<< orphan*/  I8254_MODE1 ; 
 int PCI230_ADC_IM_DIF ; 
 int PCI230_ADC_IM_MASK ; 
 int /*<<< orphan*/  comedi_8254_set_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static int pci230_ai_inttrig_convert(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     unsigned int trig_num)
{
	struct pci230_private *devpriv = dev->private;
	unsigned long irqflags;
	unsigned int delayus;

	if (trig_num)
		return -EINVAL;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	if (!devpriv->ai_cmd_started) {
		spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
		return 1;
	}
	/*
	 * Trigger conversion by toggling Z2-CT2 output.
	 * Finish with output high.
	 */
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE0);
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE1);
	/*
	 * Delay.  Should driver be responsible for this?  An
	 * alternative would be to wait until conversion is complete,
	 * but we can't tell when it's complete because the ADC busy
	 * bit has a different meaning when FIFO enabled (and when
	 * FIFO not enabled, it only works for software triggers).
	 */
	if ((devpriv->adccon & PCI230_ADC_IM_MASK) == PCI230_ADC_IM_DIF &&
	    devpriv->hwver == 0) {
		/* PCI230/260 in differential mode */
		delayus = 8;
	} else {
		/* single-ended or PCI230+/260+ */
		delayus = 4;
	}
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
	udelay(delayus);
	return 1;
}