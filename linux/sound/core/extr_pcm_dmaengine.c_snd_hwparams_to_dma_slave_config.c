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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct dma_slave_config {int dst_addr_width; int src_addr_width; int device_fc; int /*<<< orphan*/  direction; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_3_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_8_BYTES ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int params_physical_width (struct snd_pcm_hw_params const*) ; 

int snd_hwparams_to_dma_slave_config(const struct snd_pcm_substream *substream,
	const struct snd_pcm_hw_params *params,
	struct dma_slave_config *slave_config)
{
	enum dma_slave_buswidth buswidth;
	int bits;

	bits = params_physical_width(params);
	if (bits < 8 || bits > 64)
		return -EINVAL;
	else if (bits == 8)
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
	else if (bits == 16)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	else if (bits == 24)
		buswidth = DMA_SLAVE_BUSWIDTH_3_BYTES;
	else if (bits <= 32)
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
	else
		buswidth = DMA_SLAVE_BUSWIDTH_8_BYTES;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		slave_config->direction = DMA_MEM_TO_DEV;
		slave_config->dst_addr_width = buswidth;
	} else {
		slave_config->direction = DMA_DEV_TO_MEM;
		slave_config->src_addr_width = buswidth;
	}

	slave_config->device_fc = false;

	return 0;
}