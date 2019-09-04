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
struct sun4i_codec {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_codec_start_playback(struct sun4i_codec *scodec)
{
	/* Flush TX FIFO */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH),
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH));

	/* Enable DAC DRQ */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN),
			   BIT(SUN4I_CODEC_DAC_FIFOC_DAC_DRQ_EN));
}