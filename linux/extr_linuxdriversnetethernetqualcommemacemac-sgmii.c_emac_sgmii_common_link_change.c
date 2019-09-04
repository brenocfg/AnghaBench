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
struct emac_sgmii {int /*<<< orphan*/  irq; scalar_t__ base; } ;
struct emac_adapter {struct emac_sgmii phy; } ;

/* Variables and functions */
 scalar_t__ EMAC_SGMII_PHY_INTERRUPT_MASK ; 
 int /*<<< orphan*/  SGMII_ISR_MASK ; 
 int emac_sgmii_irq_clear (struct emac_adapter*,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int emac_sgmii_common_link_change(struct emac_adapter *adpt, bool linkup)
{
	struct emac_sgmii *sgmii = &adpt->phy;
	int ret;

	if (linkup) {
		/* Clear and enable interrupts */
		ret = emac_sgmii_irq_clear(adpt, 0xff);
		if (ret)
			return ret;

		writel(SGMII_ISR_MASK,
		       sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);
	} else {
		/* Disable interrupts */
		writel(0, sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);
		synchronize_irq(sgmii->irq);
	}

	return 0;
}