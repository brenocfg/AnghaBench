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
struct pci9118_private {scalar_t__ iobase_a; } ;
struct comedi_device {struct pci9118_private* private; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pci9118_amcc_int_ena(struct comedi_device *dev, bool enable)
{
	struct pci9118_private *devpriv = dev->private;
	unsigned int intcsr;

	/* enable/disable interrupt for AMCC Incoming Mailbox 4 (32-bit) */
	intcsr = inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR);
	if (enable)
		intcsr |= 0x1f00;
	else
		intcsr &= ~0x1f00;
	outl(intcsr, devpriv->iobase_a + AMCC_OP_REG_INTCSR);
}