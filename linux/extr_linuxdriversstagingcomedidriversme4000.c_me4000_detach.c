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
struct me4000_private {scalar_t__ plx_regbase; } ;
struct comedi_device {struct me4000_private* private; scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ PLX9052_INTCSR ; 
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void me4000_detach(struct comedi_device *dev)
{
	if (dev->irq) {
		struct me4000_private *devpriv = dev->private;

		/* Disable interrupts on the PLX */
		outl(0, devpriv->plx_regbase + PLX9052_INTCSR);
	}
	comedi_pci_detach(dev);
}