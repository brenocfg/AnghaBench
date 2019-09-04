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
struct artpec6_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOCCFG ; 
 int NOCCFG_ENABLE_CLK_PCIE ; 
 int NOCCFG_POWER_PCIE_IDLEREQ ; 
 int /*<<< orphan*/  PCIECFG ; 
 int PCIECFG_CISRREN ; 
 int PCIECFG_CLKREQ_B ; 
 int PCIECFG_DBG_OEN ; 
 int PCIECFG_MACRO_ENABLE ; 
 int PCIECFG_MODE_TX_DRV_EN ; 
 int PCIECFG_PCLK_ENABLE ; 
 int PCIECFG_PLL_ENABLE ; 
 int PCIECFG_REFCLK_ENABLE ; 
 int PCIECFG_RISRCREN ; 
 int artpec6_pcie_readl (struct artpec6_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  artpec6_pcie_writel (struct artpec6_pcie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void artpec6_pcie_init_phy_a6(struct artpec6_pcie *artpec6_pcie)
{
	u32 val;

	val = artpec6_pcie_readl(artpec6_pcie, PCIECFG);
	val |=  PCIECFG_RISRCREN |	/* Receiver term. 50 Ohm */
		PCIECFG_MODE_TX_DRV_EN |
		PCIECFG_CISRREN |	/* Reference clock term. 100 Ohm */
		PCIECFG_MACRO_ENABLE;
	val |= PCIECFG_REFCLK_ENABLE;
	val &= ~PCIECFG_DBG_OEN;
	val &= ~PCIECFG_CLKREQ_B;
	artpec6_pcie_writel(artpec6_pcie, PCIECFG, val);
	usleep_range(5000, 6000);

	val = artpec6_pcie_readl(artpec6_pcie, NOCCFG);
	val |= NOCCFG_ENABLE_CLK_PCIE;
	artpec6_pcie_writel(artpec6_pcie, NOCCFG, val);
	usleep_range(20, 30);

	val = artpec6_pcie_readl(artpec6_pcie, PCIECFG);
	val |= PCIECFG_PCLK_ENABLE | PCIECFG_PLL_ENABLE;
	artpec6_pcie_writel(artpec6_pcie, PCIECFG, val);
	usleep_range(6000, 7000);

	val = artpec6_pcie_readl(artpec6_pcie, NOCCFG);
	val &= ~NOCCFG_POWER_PCIE_IDLEREQ;
	artpec6_pcie_writel(artpec6_pcie, NOCCFG, val);
}