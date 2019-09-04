#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sun4i_codec {int /*<<< orphan*/  regmap; TYPE_1__* dev; int /*<<< orphan*/  reg_adc_fifoc; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_CODEC_ADC_ACTL ; 
 int /*<<< orphan*/  SUN4I_CODEC_ADC_FIFOC_FIFO_FLUSH ; 
 int SUN4I_CODEC_ADC_FIFOC_RX_TRIG_LEVEL ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_TUNE ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_field_update_bits (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sun4i_codec* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_codec_prepare_capture(struct snd_pcm_substream *substream,
				       struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);


	/* Flush RX FIFO */
	regmap_field_update_bits(scodec->reg_adc_fifoc,
				 BIT(SUN4I_CODEC_ADC_FIFOC_FIFO_FLUSH),
				 BIT(SUN4I_CODEC_ADC_FIFOC_FIFO_FLUSH));


	/* Set RX FIFO trigger level */
	regmap_field_update_bits(scodec->reg_adc_fifoc,
				 0xf << SUN4I_CODEC_ADC_FIFOC_RX_TRIG_LEVEL,
				 0x7 << SUN4I_CODEC_ADC_FIFOC_RX_TRIG_LEVEL);

	/*
	 * FIXME: Undocumented in the datasheet, but
	 *        Allwinner's code mentions that it is related
	 *        related to microphone gain
	 */
	if (of_device_is_compatible(scodec->dev->of_node,
				    "allwinner,sun4i-a10-codec") ||
	    of_device_is_compatible(scodec->dev->of_node,
				    "allwinner,sun7i-a20-codec")) {
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_ADC_ACTL,
				   0x3 << 25,
				   0x1 << 25);
	}

	if (of_device_is_compatible(scodec->dev->of_node,
				    "allwinner,sun7i-a20-codec"))
		/* FIXME: Undocumented bits */
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_TUNE,
				   0x3 << 8,
				   0x1 << 8);

	return 0;
}