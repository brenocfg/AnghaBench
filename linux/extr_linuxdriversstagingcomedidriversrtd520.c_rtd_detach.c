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
struct rtd_private {scalar_t__ lcfg; scalar_t__ las1; } ;
struct comedi_device {scalar_t__ mmio; scalar_t__ irq; struct rtd_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  rtd_reset (struct comedi_device*) ; 

__attribute__((used)) static void rtd_detach(struct comedi_device *dev)
{
	struct rtd_private *devpriv = dev->private;

	if (devpriv) {
		/* Shut down any board ops by resetting it */
		if (dev->mmio && devpriv->lcfg)
			rtd_reset(dev);
		if (dev->irq)
			free_irq(dev->irq, dev);
		if (dev->mmio)
			iounmap(dev->mmio);
		if (devpriv->las1)
			iounmap(devpriv->las1);
		if (devpriv->lcfg)
			iounmap(devpriv->lcfg);
	}
	comedi_pci_disable(dev);
}