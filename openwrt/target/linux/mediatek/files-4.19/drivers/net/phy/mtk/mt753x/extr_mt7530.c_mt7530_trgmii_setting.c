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
typedef  scalar_t__ u16 ;
struct gsw_mt753x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_PLL_GROUP10 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP11 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP2 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP4 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP5 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP6 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP7 ; 
 int GSWCK_EN ; 
 scalar_t__ NUM_TRGMII_ODT ; 
 int RG_LCCDS_C_S ; 
 int RG_LCDDS_ISO_EN ; 
 int RG_LCDDS_PWDB ; 
 int RG_SYSPLL_BIAS_EN ; 
 int RG_SYSPLL_BIAS_LPF_EN ; 
 int RG_SYSPLL_DDSFBK_EN ; 
 int RG_SYSPLL_EN_NORMAL ; 
 int RG_SYSPLL_POSDIV_S ; 
 int RG_SYSPLL_VODEN ; 
 int TRGMIICK_EN ; 
 int /*<<< orphan*/  TRGMII_GSW_CLK_CG ; 
 int /*<<< orphan*/  TRGMII_TD_ODT (scalar_t__) ; 
 int TX_DM_DRVN_S ; 
 int TX_DM_DRVP_S ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mt7530_core_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt7530_trgmii_setting(struct gsw_mt753x *gsw)
{
	u16 i;

	mt7530_core_reg_write(gsw, CORE_PLL_GROUP5, 0x0780);
	mdelay(1);
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP6, 0);
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP10, 0x87);
	mdelay(1);
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP11, 0x87);

	/* PLL BIAS enable */
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP4,
			      RG_SYSPLL_DDSFBK_EN | RG_SYSPLL_BIAS_EN);
	mdelay(1);

	/* PLL LPF enable */
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP4,
			      RG_SYSPLL_DDSFBK_EN |
			      RG_SYSPLL_BIAS_EN | RG_SYSPLL_BIAS_LPF_EN);

	/* sys PLL enable */
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP2,
			      RG_SYSPLL_EN_NORMAL | RG_SYSPLL_VODEN |
			      (1 << RG_SYSPLL_POSDIV_S));

	/* LCDDDS PWDS */
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP7,
			      (3 << RG_LCCDS_C_S) |
			      RG_LCDDS_PWDB | RG_LCDDS_ISO_EN);
	mdelay(1);

	/* Enable MT7530 TRGMII clock */
	mt7530_core_reg_write(gsw, TRGMII_GSW_CLK_CG, GSWCK_EN | TRGMIICK_EN);

	/* lower Tx Driving */
	for (i = 0 ; i < NUM_TRGMII_ODT; i++)
		mt753x_reg_write(gsw, TRGMII_TD_ODT(i),
				 (4 << TX_DM_DRVP_S) | (4 << TX_DM_DRVN_S));
}