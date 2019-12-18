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
 int /*<<< orphan*/  MT6358_AUDDEC_ANA_CON1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hp_main_output_ramp(struct mt6358_priv *priv, bool up)
{
	int i = 0, stage = 0;
	int target = 7;

	/* Enable/Reduce HPL/R main output stage step by step */
	for (i = 0; i <= target; i++) {
		stage = up ? i : target - i;
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
				   0x7 << 8, stage << 8);
		regmap_update_bits(priv->regmap, MT6358_AUDDEC_ANA_CON1,
				   0x7 << 11, stage << 11);
		usleep_range(100, 150);
	}
}