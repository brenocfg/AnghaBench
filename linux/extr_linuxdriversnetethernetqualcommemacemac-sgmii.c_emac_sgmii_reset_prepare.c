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
typedef  int u32 ;
struct emac_sgmii {scalar_t__ base; } ;
struct emac_adapter {struct emac_sgmii phy; } ;

/* Variables and functions */
 scalar_t__ EMAC_EMAC_WRAPPER_CSR2 ; 
 int PHY_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emac_sgmii_reset_prepare(struct emac_adapter *adpt)
{
	struct emac_sgmii *phy = &adpt->phy;
	u32 val;

	/* Reset PHY */
	val = readl(phy->base + EMAC_EMAC_WRAPPER_CSR2);
	writel(((val & ~PHY_RESET) | PHY_RESET), phy->base +
	       EMAC_EMAC_WRAPPER_CSR2);
	/* Ensure phy-reset command is written to HW before the release cmd */
	msleep(50);
	val = readl(phy->base + EMAC_EMAC_WRAPPER_CSR2);
	writel((val & ~PHY_RESET), phy->base + EMAC_EMAC_WRAPPER_CSR2);
	/* Ensure phy-reset release command is written to HW before initializing
	 * SGMII
	 */
	msleep(50);
}