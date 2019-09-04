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
struct xgene_phy_ctx {int dummy; } ;
typedef  enum cmu_type_t { ____Placeholder_cmu_type_t } cmu_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMU_REG32 ; 
 int /*<<< orphan*/  CMU_REG32_FORCE_VCOCAL_START_MASK ; 
 int /*<<< orphan*/  CMU_REG35 ; 
 int /*<<< orphan*/  CMU_REG35_PLL_SSC_MOD_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMU_REG36 ; 
 int /*<<< orphan*/  CMU_REG36_PLL_SSC_DSMSEL_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMU_REG36_PLL_SSC_EN_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMU_REG36_PLL_SSC_VSTEP_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMU_REG5 ; 
 int /*<<< orphan*/  CMU_REG5_PLL_RESETB_MASK ; 
 int /*<<< orphan*/  cmu_clrbits (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmu_rd (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmu_setbits (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmu_toggle1to0 (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmu_wr (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_phy_ssc_enable(struct xgene_phy_ctx *ctx,
				 enum cmu_type_t cmu_type)
{
	u32 val;

	/* Set SSC modulation value */
	cmu_rd(ctx, cmu_type, CMU_REG35, &val);
	val = CMU_REG35_PLL_SSC_MOD_SET(val, 98);
	cmu_wr(ctx, cmu_type, CMU_REG35, val);

	/* Enable SSC, set vertical step and DSM value */
	cmu_rd(ctx, cmu_type, CMU_REG36, &val);
	val = CMU_REG36_PLL_SSC_VSTEP_SET(val, 30);
	val = CMU_REG36_PLL_SSC_EN_SET(val, 1);
	val = CMU_REG36_PLL_SSC_DSMSEL_SET(val, 1);
	cmu_wr(ctx, cmu_type, CMU_REG36, val);

	/* Reset the PLL */
	cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
	cmu_setbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);

	/* Force VCO calibration to restart */
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		       CMU_REG32_FORCE_VCOCAL_START_MASK);
}