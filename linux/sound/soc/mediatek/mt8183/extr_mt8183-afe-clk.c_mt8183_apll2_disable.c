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
struct mtk_base_afe {int /*<<< orphan*/  regmap; struct mt8183_afe_private* platform_priv; } ;
struct mt8183_afe_private {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int AFE_24M_ON_MASK_SFT ; 
 int AFE_24M_ON_SFT ; 
 int /*<<< orphan*/  AFE_APLL2_TUNER_CFG ; 
 int /*<<< orphan*/  AFE_HD_ENGEN_ENABLE ; 
 size_t CLK_APLL24M ; 
 size_t CLK_APLL2_TUNER ; 
 int /*<<< orphan*/  apll2_mux_setting (struct mtk_base_afe*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void mt8183_apll2_disable(struct mtk_base_afe *afe)
{
	struct mt8183_afe_private *afe_priv = afe->platform_priv;

	regmap_update_bits(afe->regmap, AFE_HD_ENGEN_ENABLE,
			   AFE_24M_ON_MASK_SFT,
			   0x0 << AFE_24M_ON_SFT);

	regmap_update_bits(afe->regmap, AFE_APLL2_TUNER_CFG, 0x1, 0x0);

	clk_disable_unprepare(afe_priv->clk[CLK_APLL2_TUNER]);
	clk_disable_unprepare(afe_priv->clk[CLK_APLL24M]);

	apll2_mux_setting(afe, false);
}