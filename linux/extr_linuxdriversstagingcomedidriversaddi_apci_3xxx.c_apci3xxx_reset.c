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
struct comedi_device {int /*<<< orphan*/  irq; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int apci3xxx_reset(struct comedi_device *dev)
{
	unsigned int val;
	int i;

	/* Disable the interrupt */
	disable_irq(dev->irq);

	/* Clear the start command */
	writel(0, dev->mmio + 8);

	/* Reset the interrupt flags */
	val = readl(dev->mmio + 16);
	writel(val, dev->mmio + 16);

	/* clear the EOS */
	readl(dev->mmio + 20);

	/* Clear the FIFO */
	for (i = 0; i < 16; i++)
		val = readl(dev->mmio + 28);

	/* Enable the interrupt */
	enable_irq(dev->irq);

	return 0;
}