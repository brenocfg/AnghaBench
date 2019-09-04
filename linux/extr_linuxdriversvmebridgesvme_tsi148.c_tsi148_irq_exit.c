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
struct vme_bridge {struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {scalar_t__ base; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_INTC ; 
 scalar_t__ TSI148_LCSR_INTEN ; 
 scalar_t__ TSI148_LCSR_INTEO ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vme_bridge*) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 

__attribute__((used)) static void tsi148_irq_exit(struct vme_bridge *tsi148_bridge,
	struct pci_dev *pdev)
{
	struct tsi148_driver *bridge = tsi148_bridge->driver_priv;

	/* Turn off interrupts */
	iowrite32be(0x0, bridge->base + TSI148_LCSR_INTEO);
	iowrite32be(0x0, bridge->base + TSI148_LCSR_INTEN);

	/* Clear all interrupts */
	iowrite32be(0xFFFFFFFF, bridge->base + TSI148_LCSR_INTC);

	/* Detach interrupt handler */
	free_irq(pdev->irq, tsi148_bridge);
}