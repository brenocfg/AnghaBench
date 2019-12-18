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
 int /*<<< orphan*/  MT6358_GPIO_MODE3 ; 
 int /*<<< orphan*/  MT6358_GPIO_MODE3_CLR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void capture_gpio_reset(struct mt6358_priv *priv)
{
	/* set pad_aud_*_miso to GPIO mode and dir input
	 * reason:
	 * pad_aud_clk_miso, because when playback only the miso_clk
	 * will also have 26m, so will have power leak
	 * pad_aud_dat_miso*, because the pin is used as boot strap
	 */
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3_CLR,
			   0xffff, 0xffff);
	regmap_update_bits(priv->regmap, MT6358_GPIO_MODE3,
			   0xffff, 0x0000);
	regmap_update_bits(priv->regmap, MT6358_GPIO_DIR0,
			   0xf << 12, 0x0);
}