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
struct sun4i_codec {int /*<<< orphan*/  reg_adc_fifoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN ; 
 int /*<<< orphan*/  regmap_field_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_codec_start_capture(struct sun4i_codec *scodec)
{
	/* Enable ADC DRQ */
	regmap_field_update_bits(scodec->reg_adc_fifoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN),
				 BIT(SUN4I_CODEC_ADC_FIFOC_ADC_DRQ_EN));
}