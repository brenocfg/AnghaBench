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
struct vme_bridge {int /*<<< orphan*/  parent; struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {scalar_t__ base; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ TSI148_LCSR_INTEN ; 
 scalar_t__ TSI148_LCSR_INTEO ; 
 unsigned int TSI148_LCSR_INTEO_DMA0EO ; 
 unsigned int TSI148_LCSR_INTEO_DMA1EO ; 
 unsigned int TSI148_LCSR_INTEO_IACKEO ; 
 unsigned int TSI148_LCSR_INTEO_MB0EO ; 
 unsigned int TSI148_LCSR_INTEO_MB1EO ; 
 unsigned int TSI148_LCSR_INTEO_MB2EO ; 
 unsigned int TSI148_LCSR_INTEO_MB3EO ; 
 unsigned int TSI148_LCSR_INTEO_PERREO ; 
 unsigned int TSI148_LCSR_INTEO_VERREO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  iowrite32be (unsigned int,scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vme_bridge*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi148_irqhandler ; 

__attribute__((used)) static int tsi148_irq_init(struct vme_bridge *tsi148_bridge)
{
	int result;
	unsigned int tmp;
	struct pci_dev *pdev;
	struct tsi148_driver *bridge;

	pdev = to_pci_dev(tsi148_bridge->parent);

	bridge = tsi148_bridge->driver_priv;

	result = request_irq(pdev->irq,
			     tsi148_irqhandler,
			     IRQF_SHARED,
			     driver_name, tsi148_bridge);
	if (result) {
		dev_err(tsi148_bridge->parent, "Can't get assigned pci irq "
			"vector %02X\n", pdev->irq);
		return result;
	}

	/* Enable and unmask interrupts */
	tmp = TSI148_LCSR_INTEO_DMA1EO | TSI148_LCSR_INTEO_DMA0EO |
		TSI148_LCSR_INTEO_MB3EO | TSI148_LCSR_INTEO_MB2EO |
		TSI148_LCSR_INTEO_MB1EO | TSI148_LCSR_INTEO_MB0EO |
		TSI148_LCSR_INTEO_PERREO | TSI148_LCSR_INTEO_VERREO |
		TSI148_LCSR_INTEO_IACKEO;

	/* This leaves the following interrupts masked.
	 * TSI148_LCSR_INTEO_VIEEO
	 * TSI148_LCSR_INTEO_SYSFLEO
	 * TSI148_LCSR_INTEO_ACFLEO
	 */

	/* Don't enable Location Monitor interrupts here - they will be
	 * enabled when the location monitors are properly configured and
	 * a callback has been attached.
	 * TSI148_LCSR_INTEO_LM0EO
	 * TSI148_LCSR_INTEO_LM1EO
	 * TSI148_LCSR_INTEO_LM2EO
	 * TSI148_LCSR_INTEO_LM3EO
	 */

	/* Don't enable VME interrupts until we add a handler, else the board
	 * will respond to it and we don't want that unless it knows how to
	 * properly deal with it.
	 * TSI148_LCSR_INTEO_IRQ7EO
	 * TSI148_LCSR_INTEO_IRQ6EO
	 * TSI148_LCSR_INTEO_IRQ5EO
	 * TSI148_LCSR_INTEO_IRQ4EO
	 * TSI148_LCSR_INTEO_IRQ3EO
	 * TSI148_LCSR_INTEO_IRQ2EO
	 * TSI148_LCSR_INTEO_IRQ1EO
	 */

	iowrite32be(tmp, bridge->base + TSI148_LCSR_INTEO);
	iowrite32be(tmp, bridge->base + TSI148_LCSR_INTEN);

	return 0;
}