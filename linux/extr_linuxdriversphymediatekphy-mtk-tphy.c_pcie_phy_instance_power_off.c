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
struct u3phy_banks {scalar_t__ chip; } ;
struct mtk_tphy {int dummy; } ;
struct mtk_phy_instance {struct u3phy_banks u3_banks; } ;

/* Variables and functions */
 int P3C_FORCE_IP_SW_RST ; 
 int P3C_REG_IP_SW_RST ; 
 int P3C_RG_SWRST_U3_PHYD ; 
 int P3C_RG_SWRST_U3_PHYD_FORCE_EN ; 
 scalar_t__ U3P_U3_CHIP_GPIO_CTLD ; 
 scalar_t__ U3P_U3_CHIP_GPIO_CTLE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pcie_phy_instance_power_off(struct mtk_tphy *tphy,
	struct mtk_phy_instance *instance)

{
	struct u3phy_banks *bank = &instance->u3_banks;
	u32 tmp;

	tmp = readl(bank->chip + U3P_U3_CHIP_GPIO_CTLD);
	tmp |= P3C_FORCE_IP_SW_RST | P3C_REG_IP_SW_RST;
	writel(tmp, bank->chip + U3P_U3_CHIP_GPIO_CTLD);

	tmp = readl(bank->chip + U3P_U3_CHIP_GPIO_CTLE);
	tmp |= P3C_RG_SWRST_U3_PHYD_FORCE_EN | P3C_RG_SWRST_U3_PHYD;
	writel(tmp, bank->chip + U3P_U3_CHIP_GPIO_CTLE);
}