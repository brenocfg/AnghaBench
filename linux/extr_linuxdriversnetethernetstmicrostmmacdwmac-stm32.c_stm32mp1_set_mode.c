#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct stm32_dwmac {TYPE_1__* ops; int /*<<< orphan*/  regmap; int /*<<< orphan*/  int_phyclk; int /*<<< orphan*/  mode_reg; } ;
struct plat_stmmacenet_data {int interface; struct stm32_dwmac* bsp_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  syscfg_eth_mask; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_INTERFACE_MODE_GMII 131 
#define  PHY_INTERFACE_MODE_MII 130 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int SYSCFG_PMCR_ETH_CLK_SEL ; 
 int SYSCFG_PMCR_ETH_REF_CLK_SEL ; 
 int SYSCFG_PMCR_ETH_SEL_GMII ; 
 int SYSCFG_PMCR_ETH_SEL_MII ; 
 int SYSCFG_PMCR_ETH_SEL_RGMII ; 
 int SYSCFG_PMCR_ETH_SEL_RMII ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32mp1_set_mode(struct plat_stmmacenet_data *plat_dat)
{
	struct stm32_dwmac *dwmac = plat_dat->bsp_priv;
	u32 reg = dwmac->mode_reg;
	int val;

	switch (plat_dat->interface) {
	case PHY_INTERFACE_MODE_MII:
		val = SYSCFG_PMCR_ETH_SEL_MII;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_MII\n");
		break;
	case PHY_INTERFACE_MODE_GMII:
		val = SYSCFG_PMCR_ETH_SEL_GMII;
		if (dwmac->int_phyclk)
			val |= SYSCFG_PMCR_ETH_CLK_SEL;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_GMII\n");
		break;
	case PHY_INTERFACE_MODE_RMII:
		val = SYSCFG_PMCR_ETH_SEL_RMII;
		if (dwmac->int_phyclk)
			val |= SYSCFG_PMCR_ETH_REF_CLK_SEL;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_RMII\n");
		break;
	case PHY_INTERFACE_MODE_RGMII:
		val = SYSCFG_PMCR_ETH_SEL_RGMII;
		if (dwmac->int_phyclk)
			val |= SYSCFG_PMCR_ETH_CLK_SEL;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_RGMII\n");
		break;
	default:
		pr_debug("SYSCFG init :  Do not manage %d interface\n",
			 plat_dat->interface);
		/* Do not manage others interfaces */
		return -EINVAL;
	}

	return regmap_update_bits(dwmac->regmap, reg,
				 dwmac->ops->syscfg_eth_mask, val);
}