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
struct pc236_private {scalar_t__ lcr_iobase; } ;
struct comedi_device {struct pc236_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI236_INTR_DISABLE ; 
 int /*<<< orphan*/  PCI236_INTR_ENABLE ; 
 scalar_t__ PLX9052_INTCSR ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pci236_intr_update_cb(struct comedi_device *dev, bool enable)
{
	struct pc236_private *devpriv = dev->private;

	/* this will also clear the "local interrupt 1" latch */
	outl(enable ? PCI236_INTR_ENABLE : PCI236_INTR_DISABLE,
	     devpriv->lcr_iobase + PLX9052_INTCSR);
}