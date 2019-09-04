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
typedef  int u32 ;
struct sun4i_codec {int /*<<< orphan*/  regmap; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_FIR_VERSION ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_SEND_LASAT ; 
 int SUN4I_CODEC_DAC_FIFOC_TX_TRIG_LEVEL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sun4i_codec* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_codec_prepare_playback(struct snd_pcm_substream *substream,
					struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);
	u32 val;

	/* Flush the TX FIFO */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH),
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIFO_FLUSH));

	/* Set TX FIFO Empty Trigger Level */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   0x3f << SUN4I_CODEC_DAC_FIFOC_TX_TRIG_LEVEL,
			   0xf << SUN4I_CODEC_DAC_FIFOC_TX_TRIG_LEVEL);

	if (substream->runtime->rate > 32000)
		/* Use 64 bits FIR filter */
		val = 0;
	else
		/* Use 32 bits FIR filter */
		val = BIT(SUN4I_CODEC_DAC_FIFOC_FIR_VERSION);

	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_FIR_VERSION),
			   val);

	/* Send zeros when we have an underrun */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_SEND_LASAT),
			   0);

	return 0;
}