#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  addr_width; } ;
struct sun4i_codec {TYPE_1__ playback_dma_data; int /*<<< orphan*/  regmap; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int min; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC ; 
 int SUN4I_CODEC_DAC_FIFOC_DAC_FS ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_MONO_EN ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE ; 
 int /*<<< orphan*/  SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS ; 
 TYPE_2__* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sun4i_codec_hw_params_playback(struct sun4i_codec *scodec,
					  struct snd_pcm_hw_params *params,
					  unsigned int hwrate)
{
	u32 val;

	/* Set DAC sample rate */
	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   7 << SUN4I_CODEC_DAC_FIFOC_DAC_FS,
			   hwrate << SUN4I_CODEC_DAC_FIFOC_DAC_FS);

	/* Set the number of channels we want to use */
	if (params_channels(params) == 1)
		val = BIT(SUN4I_CODEC_DAC_FIFOC_MONO_EN);
	else
		val = 0;

	regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
			   BIT(SUN4I_CODEC_DAC_FIFOC_MONO_EN),
			   val);

	/* Set the number of sample bits to either 16 or 24 bits */
	if (hw_param_interval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS)->min == 32) {
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS),
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS));

		/* Set TX FIFO mode to padding the LSBs with 0 */
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE),
				   0);

		scodec->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	} else {
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_SAMPLE_BITS),
				   0);

		/* Set TX FIFO mode to repeat the MSB */
		regmap_update_bits(scodec->regmap, SUN4I_CODEC_DAC_FIFOC,
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE),
				   BIT(SUN4I_CODEC_DAC_FIFOC_TX_FIFO_MODE));

		scodec->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	}

	return 0;
}