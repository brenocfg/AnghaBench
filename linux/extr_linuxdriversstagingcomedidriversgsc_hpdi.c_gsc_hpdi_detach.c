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
struct hpdi_private {scalar_t__ plx9080_mmio; } ;
struct comedi_device {scalar_t__ mmio; scalar_t__ irq; struct hpdi_private* private; } ;

/* Variables and functions */
 scalar_t__ PLX_REG_INTCSR ; 
 int /*<<< orphan*/  comedi_pci_disable (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  gsc_hpdi_free_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void gsc_hpdi_detach(struct comedi_device *dev)
{
	struct hpdi_private *devpriv = dev->private;

	if (dev->irq)
		free_irq(dev->irq, dev);
	if (devpriv) {
		if (devpriv->plx9080_mmio) {
			writel(0, devpriv->plx9080_mmio + PLX_REG_INTCSR);
			iounmap(devpriv->plx9080_mmio);
		}
		if (dev->mmio)
			iounmap(dev->mmio);
	}
	comedi_pci_disable(dev);
	gsc_hpdi_free_dma(dev);
}