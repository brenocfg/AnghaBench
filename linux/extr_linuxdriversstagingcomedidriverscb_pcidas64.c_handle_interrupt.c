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
struct pcidas64_private {scalar_t__ plx9080_iobase; scalar_t__ main_iobase; } ;
struct comedi_device {int /*<<< orphan*/  attached; struct pcidas64_private* private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ HW_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PLX_INTCSR_LDBIA ; 
 scalar_t__ PLX_REG_INTCSR ; 
 scalar_t__ PLX_REG_L2PDBELL ; 
 int /*<<< orphan*/  handle_ai_interrupt (struct comedi_device*,unsigned short,int) ; 
 int /*<<< orphan*/  handle_ao_interrupt (struct comedi_device*,unsigned short,int) ; 
 int readl (scalar_t__) ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t handle_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct pcidas64_private *devpriv = dev->private;
	unsigned short status;
	u32 plx_status;
	u32 plx_bits;

	plx_status = readl(devpriv->plx9080_iobase + PLX_REG_INTCSR);
	status = readw(devpriv->main_iobase + HW_STATUS_REG);

	/*
	 * an interrupt before all the postconfig stuff gets done could
	 * cause a NULL dereference if we continue through the
	 * interrupt handler
	 */
	if (!dev->attached)
		return IRQ_HANDLED;

	handle_ai_interrupt(dev, status, plx_status);
	handle_ao_interrupt(dev, status, plx_status);

	/* clear possible plx9080 interrupt sources */
	if (plx_status & PLX_INTCSR_LDBIA) {
		/* clear local doorbell interrupt */
		plx_bits = readl(devpriv->plx9080_iobase + PLX_REG_L2PDBELL);
		writel(plx_bits, devpriv->plx9080_iobase + PLX_REG_L2PDBELL);
	}

	return IRQ_HANDLED;
}