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
struct comedi_device {struct apci1500_private* private; } ;
struct apci1500_private {scalar_t__ amcc; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void apci1500_detach(struct comedi_device *dev)
{
	struct apci1500_private *devpriv = dev->private;

	if (devpriv->amcc)
		outl(0x0, devpriv->amcc + AMCC_OP_REG_INTCSR);
	comedi_pci_detach(dev);
}