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
 int /*<<< orphan*/  MT6358_GPIO_DIR0 ; 
 int /*<<< orphan*/  MT6358_GPIO_MODE2 ; 
 int /*<<< orphan*/  MT6358_GPIO_MODE2_CLR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void playback_gpio_reset(struct mt6358_priv *priv)
{
	/* set pad_aud_*_mosi to GPIO mode and dir input
	 * reason:
	 * pad_aud_dat_mosi*, because the pin is used as boot strap
	 * don't clean clk/sync, for mtkaif protocol 2
	 */
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2_CLR,
			   0x01f8, 0x01f8);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE2,
			   0x01f8, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_GPIO_DIR0,
			   0xf << 8, 0x0);
}