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
struct s626_private {scalar_t__ ai_cmd_running; } ;
struct comedi_device {scalar_t__ mmio; struct s626_private* private; } ;

/* Variables and functions */
 int S626_ACON1_BASE ; 
 int S626_IRQ_GPIO3 ; 
 int S626_IRQ_RPS1 ; 
 int S626_MC1_SHUTDOWN ; 
 scalar_t__ S626_P_ACON1 ; 
 scalar_t__ S626_P_IER ; 
 scalar_t__ S626_P_ISR ; 
 scalar_t__ S626_P_MC1 ; 
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  s626_free_dma_buffers (struct comedi_device*) ; 
 int /*<<< orphan*/  s626_write_misc2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s626_detach(struct comedi_device *dev)
{
	struct s626_private *devpriv = dev->private;

	if (devpriv) {
		/* stop ai_command */
		devpriv->ai_cmd_running = 0;

		if (dev->mmio) {
			/* interrupt mask */
			/* Disable master interrupt */
			writel(0, dev->mmio + S626_P_IER);
			/* Clear board's IRQ status flag */
			writel(S626_IRQ_GPIO3 | S626_IRQ_RPS1,
			       dev->mmio + S626_P_ISR);

			/* Disable the watchdog timer and battery charger. */
			s626_write_misc2(dev, 0);

			/* Close all interfaces on 7146 device */
			writel(S626_MC1_SHUTDOWN, dev->mmio + S626_P_MC1);
			writel(S626_ACON1_BASE, dev->mmio + S626_P_ACON1);
		}
	}
	comedi_pci_detach(dev);
	s626_free_dma_buffers(dev);
}