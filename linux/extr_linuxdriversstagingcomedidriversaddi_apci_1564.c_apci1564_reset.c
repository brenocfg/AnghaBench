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
struct comedi_device {scalar_t__ iobase; struct apci1564_private* private; } ;
struct apci1564_private {long counters; scalar_t__ timer; } ;

/* Variables and functions */
 unsigned long ADDI_TCW_CTRL_REG ; 
 scalar_t__ ADDI_TCW_RELOAD_REG ; 
 scalar_t__ APCI1564_COUNTER (int) ; 
 scalar_t__ APCI1564_DI_INT_MODE1_REG ; 
 scalar_t__ APCI1564_DI_INT_MODE2_REG ; 
 scalar_t__ APCI1564_DI_INT_STATUS_REG ; 
 scalar_t__ APCI1564_DI_IRQ_REG ; 
 scalar_t__ APCI1564_DO_INT_CTRL_REG ; 
 scalar_t__ APCI1564_DO_REG ; 
 scalar_t__ APCI1564_WDOG_IOBASE ; 
 int /*<<< orphan*/  addi_watchdog_reset (scalar_t__) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int apci1564_reset(struct comedi_device *dev)
{
	struct apci1564_private *devpriv = dev->private;

	/* Disable the input interrupts and reset status register */
	outl(0x0, dev->iobase + APCI1564_DI_IRQ_REG);
	inl(dev->iobase + APCI1564_DI_INT_STATUS_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE1_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE2_REG);

	/* Reset the output channels and disable interrupts */
	outl(0x0, dev->iobase + APCI1564_DO_REG);
	outl(0x0, dev->iobase + APCI1564_DO_INT_CTRL_REG);

	/* Reset the watchdog registers */
	addi_watchdog_reset(dev->iobase + APCI1564_WDOG_IOBASE);

	/* Reset the timer registers */
	outl(0x0, devpriv->timer + ADDI_TCW_CTRL_REG);
	outl(0x0, devpriv->timer + ADDI_TCW_RELOAD_REG);

	if (devpriv->counters) {
		unsigned long iobase = devpriv->counters + ADDI_TCW_CTRL_REG;

		/* Reset the counter registers */
		outl(0x0, iobase + APCI1564_COUNTER(0));
		outl(0x0, iobase + APCI1564_COUNTER(1));
		outl(0x0, iobase + APCI1564_COUNTER(2));
	}

	return 0;
}