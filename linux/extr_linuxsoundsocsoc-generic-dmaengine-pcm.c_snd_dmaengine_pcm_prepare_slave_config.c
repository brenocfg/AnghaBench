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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int dummy; } ;
struct dma_slave_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dmaengine_pcm_set_config_from_dai_data (struct snd_pcm_substream*,struct snd_dmaengine_dai_dma_data*,struct dma_slave_config*) ; 
 int snd_hwparams_to_dma_slave_config (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct dma_slave_config*) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

int snd_dmaengine_pcm_prepare_slave_config(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct dma_slave_config *slave_config)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_dmaengine_dai_dma_data *dma_data;
	int ret;

	dma_data = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);

	ret = snd_hwparams_to_dma_slave_config(substream, params, slave_config);
	if (ret)
		return ret;

	snd_dmaengine_pcm_set_config_from_dai_data(substream, dma_data,
		slave_config);

	return 0;
}