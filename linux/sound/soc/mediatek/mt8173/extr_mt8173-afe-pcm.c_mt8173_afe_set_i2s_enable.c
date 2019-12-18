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
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_I2S_CON1 ; 
 int /*<<< orphan*/  AFE_I2S_CON2 ; 
 unsigned int AFE_I2S_CON2_EN ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mt8173_afe_set_i2s_enable(struct mtk_base_afe *afe, bool enable)
{
	unsigned int val;

	regmap_read(afe->regmap, AFE_I2S_CON2, &val);
	if (!!(val & AFE_I2S_CON2_EN) == enable)
		return;

	/* input */
	regmap_update_bits(afe->regmap, AFE_I2S_CON2, 0x1, enable);

	/* output */
	regmap_update_bits(afe->regmap, AFE_I2S_CON1, 0x1, enable);
}