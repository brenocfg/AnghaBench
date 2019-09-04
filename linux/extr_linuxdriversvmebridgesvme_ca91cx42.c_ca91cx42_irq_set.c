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
struct vme_bridge {int /*<<< orphan*/  parent; struct ca91cx42_driver* driver_priv; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct ca91cx42_driver {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CA91CX42_LINT_VIRQ ; 
 scalar_t__ LINT_EN ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca91cx42_irq_set(struct vme_bridge *ca91cx42_bridge, int level,
	int state, int sync)

{
	struct pci_dev *pdev;
	u32 tmp;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Enable IRQ level */
	tmp = ioread32(bridge->base + LINT_EN);

	if (state == 0)
		tmp &= ~CA91CX42_LINT_VIRQ[level];
	else
		tmp |= CA91CX42_LINT_VIRQ[level];

	iowrite32(tmp, bridge->base + LINT_EN);

	if ((state == 0) && (sync != 0)) {
		pdev = to_pci_dev(ca91cx42_bridge->parent);

		synchronize_irq(pdev->irq);
	}
}