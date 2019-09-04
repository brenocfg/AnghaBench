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
typedef  int /*<<< orphan*/  u32 ;
struct vme_bridge {int /*<<< orphan*/  parent; struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {scalar_t__ base; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_INTEN ; 
 int /*<<< orphan*/ * TSI148_LCSR_INTEN_IRQEN ; 
 scalar_t__ TSI148_LCSR_INTEO ; 
 int /*<<< orphan*/ * TSI148_LCSR_INTEO_IRQEO ; 
 int /*<<< orphan*/  ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi148_irq_set(struct vme_bridge *tsi148_bridge, int level,
	int state, int sync)
{
	struct pci_dev *pdev;
	u32 tmp;
	struct tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	/* We need to do the ordering differently for enabling and disabling */
	if (state == 0) {
		tmp = ioread32be(bridge->base + TSI148_LCSR_INTEN);
		tmp &= ~TSI148_LCSR_INTEN_IRQEN[level - 1];
		iowrite32be(tmp, bridge->base + TSI148_LCSR_INTEN);

		tmp = ioread32be(bridge->base + TSI148_LCSR_INTEO);
		tmp &= ~TSI148_LCSR_INTEO_IRQEO[level - 1];
		iowrite32be(tmp, bridge->base + TSI148_LCSR_INTEO);

		if (sync != 0) {
			pdev = to_pci_dev(tsi148_bridge->parent);
			synchronize_irq(pdev->irq);
		}
	} else {
		tmp = ioread32be(bridge->base + TSI148_LCSR_INTEO);
		tmp |= TSI148_LCSR_INTEO_IRQEO[level - 1];
		iowrite32be(tmp, bridge->base + TSI148_LCSR_INTEO);

		tmp = ioread32be(bridge->base + TSI148_LCSR_INTEN);
		tmp |= TSI148_LCSR_INTEN_IRQEN[level - 1];
		iowrite32be(tmp, bridge->base + TSI148_LCSR_INTEN);
	}
}