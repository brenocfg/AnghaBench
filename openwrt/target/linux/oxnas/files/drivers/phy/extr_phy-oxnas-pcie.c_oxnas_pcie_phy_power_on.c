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
struct phy {int dummy; } ;
struct oxnas_pcie_phy {scalar_t__ membase; } ;

/* Variables and functions */
 int ADDR_VAL (int) ; 
 int CAP_DATA ; 
 int DATA_VAL (int) ; 
 scalar_t__ PHY_ADDR ; 
 scalar_t__ PHY_DATA ; 
 int WRITE_EN ; 
 struct oxnas_pcie_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int oxnas_pcie_phy_power_on(struct phy *phy)
{
	struct oxnas_pcie_phy *pciephy = phy_get_drvdata(phy);

	/* Enable PCIe Pre-Emphasis: What these value means? */
	writel(ADDR_VAL(0x0014), pciephy->membase + PHY_ADDR);
	writel(DATA_VAL(0xce10) | CAP_DATA, pciephy->membase + PHY_DATA);
	writel(DATA_VAL(0xce10) | WRITE_EN, pciephy->membase + PHY_DATA);

	writel(ADDR_VAL(0x2004), pciephy->membase + PHY_ADDR);
	writel(DATA_VAL(0x82c7) | CAP_DATA, pciephy->membase + PHY_DATA);
	writel(DATA_VAL(0x82c7) | WRITE_EN, pciephy->membase + PHY_DATA);

	return 0;
}