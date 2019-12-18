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
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON13 ; 
 int /*<<< orphan*/  RG_AUDGLB_PWRDN_VA28_MASK_SFT ; 
 int RG_AUDGLB_PWRDN_VA28_SFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt6358_set_aud_global_bias(struct mt6358_priv *priv, bool enable)
{
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON13,
			   RG_AUDGLB_PWRDN_VA28_MASK_SFT,
			   (enable ? 0 : 1) << RG_AUDGLB_PWRDN_VA28_SFT);
	return 0;
}