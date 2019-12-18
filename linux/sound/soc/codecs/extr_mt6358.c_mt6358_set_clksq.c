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
struct mt6358_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT6358_AUDENC_ANA_CON6 ; 
 int /*<<< orphan*/  RG_CLKSQ_EN_MASK_SFT ; 
 int RG_CLKSQ_EN_SFT ; 
 int /*<<< orphan*/  RG_CLKSQ_IN_SEL_TEST_MASK_SFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt6358_set_clksq(struct mt6358_priv *priv, bool enable)
{
	/* audio clk source from internal dcxo */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON6,
			   RG_CLKSQ_IN_SEL_TEST_MASK_SFT,
			   0x0);

	/* Enable/disable CLKSQ 26MHz */
	regmap_update_bits(priv->regmap, MT6358_AUDENC_ANA_CON6,
			   RG_CLKSQ_EN_MASK_SFT,
			   (enable ? 1 : 0) << RG_CLKSQ_EN_SFT);
	return 0;
}