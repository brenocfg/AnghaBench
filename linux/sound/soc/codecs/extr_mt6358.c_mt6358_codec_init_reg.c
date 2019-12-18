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
 int /*<<< orphan*/  MT6358_ACCDET_CON13 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON0 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON6 ; 
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON7 ; 
 int /*<<< orphan*/  MT6358_DRV_CON3 ; 
 int RG_AUDHPLSCDISABLE_VAUDP15_MASK_SFT ; 
 int RG_AUDHPLSCDISABLE_VAUDP15_SFT ; 
 int RG_AUDHPRSCDISABLE_VAUDP15_MASK_SFT ; 
 int RG_AUDHPRSCDISABLE_VAUDP15_SFT ; 
 int RG_AUDHSSCDISABLE_VAUDP15_MASK_SFT ; 
 int RG_AUDHSSCDISABLE_VAUDP15_SFT ; 
 int RG_AUDLOLSCDISABLE_VAUDP15_MASK_SFT ; 
 int RG_AUDLOLSCDISABLE_VAUDP15_SFT ; 
 int /*<<< orphan*/  capture_gpio_reset (struct mt6358_priv*) ; 
 int /*<<< orphan*/  playback_gpio_reset (struct mt6358_priv*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt6358_codec_init_reg(struct mt6358_priv *priv)
{
	/* Disable HeadphoneL/HeadphoneR short circuit protection */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   RG_AUDHPLSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDHPLSCDISABLE_VAUDP15_SFT);
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON0,
			   RG_AUDHPRSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDHPRSCDISABLE_VAUDP15_SFT);
	/* Disable voice short circuit protection */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON6,
			   RG_AUDHSSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDHSSCDISABLE_VAUDP15_SFT);
	/* disable LO buffer left short circuit protection */
	regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON7,
			   RG_AUDLOLSCDISABLE_VAUDP15_MASK_SFT,
			   0x1 << RG_AUDLOLSCDISABLE_VAUDP15_SFT);

	/* accdet s/w enable */
	regmap_update_bits(priv->regmap, MT6358_ACCDET_CON13,
			   0xFFFF, 0x700E);

	/* gpio miso driving set to 4mA */
	regmap_write(priv->regmap, MT6358_DRV_CON3, 0x8888);

	/* set gpio */
	playback_gpio_reset(priv);
	capture_gpio_reset(priv);
}