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
struct ux500_msp_dma_params {void* tx_rx_addr; } ;
struct snd_soc_pcm_runtime {TYPE_2__* cpu_dai; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {void* addr; } ;
struct msp_i2s_platform_data {int dummy; } ;
struct dma_slave_config {int dst_maxburst; int src_maxburst; void* src_addr; void* dst_addr; void* dst_addr_width; void* src_addr_width; } ;
typedef  void* dma_addr_t ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {struct msp_i2s_platform_data* platform_data; } ;

/* Variables and functions */
 void* DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int snd_hwparams_to_dma_slave_config (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct dma_slave_config*) ; 
 void* snd_soc_dai_get_dma_data (TYPE_2__*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int ux500_pcm_prepare_slave_config(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct dma_slave_config *slave_config)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct msp_i2s_platform_data *pdata = rtd->cpu_dai->dev->platform_data;
	struct snd_dmaengine_dai_dma_data *snd_dma_params;
	struct ux500_msp_dma_params *ste_dma_params;
	dma_addr_t dma_addr;
	int ret;

	if (pdata) {
		ste_dma_params =
			snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
		dma_addr = ste_dma_params->tx_rx_addr;
	} else {
		snd_dma_params =
			snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
		dma_addr = snd_dma_params->addr;
	}

	ret = snd_hwparams_to_dma_slave_config(substream, params, slave_config);
	if (ret)
		return ret;

	slave_config->dst_maxburst = 4;
	slave_config->src_maxburst = 4;

	slave_config->src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		slave_config->dst_addr = dma_addr;
	else
		slave_config->src_addr = dma_addr;

	return 0;
}