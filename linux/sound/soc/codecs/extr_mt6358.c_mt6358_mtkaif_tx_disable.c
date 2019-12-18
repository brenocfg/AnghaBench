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
 int /*<<< orphan*/  MT6358_AFE_AUD_PAD_TOP ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mt6358_mtkaif_tx_disable(struct mt6358_priv *priv)
{
	/* disable aud_pad TX fifos */
	regmap_update_bits(priv->regmap, MT6358_AFE_AUD_PAD_TOP,
			   0xff00, 0x3000);
	return 0;
}