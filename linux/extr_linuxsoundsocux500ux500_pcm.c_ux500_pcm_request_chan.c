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
typedef  void* u16 ;
struct ux500_msp_dma_params {int data_size; struct stedma40_chan_cfg* dma_cfg; } ;
struct TYPE_4__ {void* data_width; } ;
struct TYPE_3__ {void* data_width; } ;
struct stedma40_chan_cfg {TYPE_2__ dst_info; TYPE_1__ src_info; } ;
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 void* DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 void* DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct dma_chan* snd_dmaengine_pcm_request_channel (int /*<<< orphan*/ ,struct stedma40_chan_cfg*) ; 
 struct ux500_msp_dma_params* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stedma40_filter ; 

__attribute__((used)) static struct dma_chan *ux500_pcm_request_chan(struct snd_soc_pcm_runtime *rtd,
	struct snd_pcm_substream *substream)
{
	struct snd_soc_dai *dai = rtd->cpu_dai;
	u16 per_data_width, mem_data_width;
	struct stedma40_chan_cfg *dma_cfg;
	struct ux500_msp_dma_params *dma_params;

	dma_params = snd_soc_dai_get_dma_data(dai, substream);
	dma_cfg = dma_params->dma_cfg;

	mem_data_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	switch (dma_params->data_size) {
	case 32:
		per_data_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		break;
	case 16:
		per_data_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		break;
	case 8:
		per_data_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		break;
	default:
		per_data_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		dma_cfg->src_info.data_width = mem_data_width;
		dma_cfg->dst_info.data_width = per_data_width;
	} else {
		dma_cfg->src_info.data_width = per_data_width;
		dma_cfg->dst_info.data_width = mem_data_width;
	}

	return snd_dmaengine_pcm_request_channel(stedma40_filter, dma_cfg);
}