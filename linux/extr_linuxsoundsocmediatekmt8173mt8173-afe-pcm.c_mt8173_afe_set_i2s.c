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
 int /*<<< orphan*/  AFE_ADDA2_TOP_CON0 ; 
 int /*<<< orphan*/  AFE_ADDA_TOP_CON0 ; 
 int /*<<< orphan*/  AFE_I2S_CON1 ; 
 int AFE_I2S_CON1_EN ; 
 unsigned int AFE_I2S_CON1_FORMAT_I2S ; 
 unsigned int AFE_I2S_CON1_LOW_JITTER_CLK ; 
 unsigned int AFE_I2S_CON1_RATE (int) ; 
 int /*<<< orphan*/  AFE_I2S_CON2 ; 
 int AFE_I2S_CON2_EN ; 
 unsigned int AFE_I2S_CON2_FORMAT_I2S ; 
 unsigned int AFE_I2S_CON2_LOW_JITTER_CLK ; 
 unsigned int AFE_I2S_CON2_RATE (int) ; 
 int EINVAL ; 
 int mt8173_afe_i2s_fs (unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int mt8173_afe_set_i2s(struct mtk_base_afe *afe, unsigned int rate)
{
	unsigned int val;
	int fs = mt8173_afe_i2s_fs(rate);

	if (fs < 0)
		return -EINVAL;

	/* from external ADC */
	regmap_update_bits(afe->regmap, AFE_ADDA_TOP_CON0, 0x1, 0x1);
	regmap_update_bits(afe->regmap, AFE_ADDA2_TOP_CON0, 0x1, 0x1);

	/* set input */
	val = AFE_I2S_CON2_LOW_JITTER_CLK |
	      AFE_I2S_CON2_RATE(fs) |
	      AFE_I2S_CON2_FORMAT_I2S;

	regmap_update_bits(afe->regmap, AFE_I2S_CON2, ~AFE_I2S_CON2_EN, val);

	/* set output */
	val = AFE_I2S_CON1_LOW_JITTER_CLK |
	      AFE_I2S_CON1_RATE(fs) |
	      AFE_I2S_CON1_FORMAT_I2S;

	regmap_update_bits(afe->regmap, AFE_I2S_CON1, ~AFE_I2S_CON1_EN, val);
	return 0;
}