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
struct reg_sequence {int member_0; int member_1; } ;
struct ad193x_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct reg_sequence const*) ; 
 scalar_t__ ad193x_has_adc (struct ad193x_priv*) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,struct reg_sequence const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad193x_reg_default_init(struct ad193x_priv *ad193x)
{
	static const struct reg_sequence reg_init[] = {
		{  0, 0x99 },	/* PLL_CLK_CTRL0: pll input: mclki/xi 12.288Mhz */
		{  1, 0x04 },	/* PLL_CLK_CTRL1: no on-chip Vref */
		{  2, 0x40 },	/* DAC_CTRL0: TDM mode */
		{  3, 0x00 },	/* DAC_CTRL1: reset */
		{  4, 0x1A },	/* DAC_CTRL2: 48kHz de-emphasis, unmute dac */
		{  5, 0x00 },	/* DAC_CHNL_MUTE: unmute DAC channels */
		{  6, 0x00 },	/* DAC_L1_VOL: no attenuation */
		{  7, 0x00 },	/* DAC_R1_VOL: no attenuation */
		{  8, 0x00 },	/* DAC_L2_VOL: no attenuation */
		{  9, 0x00 },	/* DAC_R2_VOL: no attenuation */
		{ 10, 0x00 },	/* DAC_L3_VOL: no attenuation */
		{ 11, 0x00 },	/* DAC_R3_VOL: no attenuation */
		{ 12, 0x00 },	/* DAC_L4_VOL: no attenuation */
		{ 13, 0x00 },	/* DAC_R4_VOL: no attenuation */
	};
	static const struct reg_sequence reg_adc_init[] = {
		{ 14, 0x03 },	/* ADC_CTRL0: high-pass filter enable */
		{ 15, 0x43 },	/* ADC_CTRL1: sata delay=1, adc aux mode */
		{ 16, 0x00 },	/* ADC_CTRL2: reset */
	};

	regmap_multi_reg_write(ad193x->regmap, reg_init, ARRAY_SIZE(reg_init));

	if (ad193x_has_adc(ad193x)) {
		regmap_multi_reg_write(ad193x->regmap, reg_adc_init,
				       ARRAY_SIZE(reg_adc_init));
	}
}