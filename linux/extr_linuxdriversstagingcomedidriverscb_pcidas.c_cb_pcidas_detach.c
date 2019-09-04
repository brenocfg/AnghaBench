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
struct comedi_device {struct cb_pcidas_private* private; } ;
struct cb_pcidas_private {int /*<<< orphan*/  ao_pacer; scalar_t__ amcc; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 int /*<<< orphan*/  INTCSR_INBOX_INTR_STATUS ; 
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cb_pcidas_detach(struct comedi_device *dev)
{
	struct cb_pcidas_private *devpriv = dev->private;

	if (devpriv) {
		if (devpriv->amcc)
			outl(INTCSR_INBOX_INTR_STATUS,
			     devpriv->amcc + AMCC_OP_REG_INTCSR);
		kfree(devpriv->ao_pacer);
	}
	comedi_pci_detach(dev);
}