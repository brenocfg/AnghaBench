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
struct mt6358_priv {int mtkaif_protocol; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT6358_AFE_ADDA_MTKAIF_CFG0 ; 
 int /*<<< orphan*/  MT6358_AFE_AUD_PAD_TOP ; 
#define  MT6358_MTKAIF_PROTOCOL_1 130 
#define  MT6358_MTKAIF_PROTOCOL_2 129 
#define  MT6358_MTKAIF_PROTOCOL_2_CLK_P2 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mt6358_mtkaif_tx_enable(struct mt6358_priv *priv)
{
	switch (priv->mtkaif_protocol) {
	case MT6358_MTKAIF_PROTOCOL_2_CLK_P2:
		/* MTKAIF TX format setting */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0010);
		/* enable aud_pad TX fifos */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3800);
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3900);
		break;
	case MT6358_MTKAIF_PROTOCOL_2:
		/* MTKAIF TX format setting */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0010);
		/* enable aud_pad TX fifos */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3100);
		break;
	case MT6358_MTKAIF_PROTOCOL_1:
	default:
		/* MTKAIF TX format setting */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_ADDA_MTKAIF_CFG0,
				   0xffff, 0x0000);
		/* enable aud_pad TX fifos */
		regmap_update_bits(priv->regmap,
				   MT6358_AFE_AUD_PAD_TOP,
				   0xff00, 0x3100);
		break;
	}
	return 0;
}