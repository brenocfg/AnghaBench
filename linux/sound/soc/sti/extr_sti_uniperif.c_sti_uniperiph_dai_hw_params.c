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
struct uniperif {scalar_t__ type; } ;
struct TYPE_2__ {struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_1__ dai_data; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int maxburst; } ;

/* Variables and functions */
 scalar_t__ SND_ST_UNIPERIF_TYPE_TDM ; 
 int UNIPERIF_FIFO_FRAMES ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct sti_uniperiph_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

int sti_uniperiph_dai_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *uni = priv->dai_data.uni;
	struct snd_dmaengine_dai_dma_data *dma_data;
	int transfer_size;

	if (uni->type == SND_ST_UNIPERIF_TYPE_TDM)
		/* transfer size = user frame size (in 32-bits FIFO cell) */
		transfer_size = snd_soc_params_to_frame_size(params) / 32;
	else
		transfer_size = params_channels(params) * UNIPERIF_FIFO_FRAMES;

	dma_data = snd_soc_dai_get_dma_data(dai, substream);
	dma_data->maxburst = transfer_size;

	return 0;
}