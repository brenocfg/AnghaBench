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
struct pcidas64_private {int adc_control1_bits; scalar_t__ main_iobase; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct pcidas64_private* private; } ;

/* Variables and functions */
 scalar_t__ ADC_CONTROL0_REG ; 
 scalar_t__ ADC_CONTROL1_REG ; 
 int ADC_DMA_DISABLE_BIT ; 
 int ADC_GATE_LEVEL_BIT ; 
 int ADC_SOFT_GATE_BITS ; 
 int ADC_SW_GATE_BIT ; 
 int /*<<< orphan*/  disable_ai_interrupts (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void disable_ai_pacing(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;
	unsigned long flags;

	disable_ai_interrupts(dev);

	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->adc_control1_bits &= ~ADC_SW_GATE_BIT;
	writew(devpriv->adc_control1_bits,
	       devpriv->main_iobase + ADC_CONTROL1_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* disable pacing, triggering, etc */
	writew(ADC_DMA_DISABLE_BIT | ADC_SOFT_GATE_BITS | ADC_GATE_LEVEL_BIT,
	       devpriv->main_iobase + ADC_CONTROL0_REG);
}