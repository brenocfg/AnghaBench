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
struct snd_pcm_substream {int /*<<< orphan*/  dma_buffer; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int dummy; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int dmaengine_slave_config (struct dma_chan*,struct dma_slave_config*) ; 
 struct dma_chan* snd_dmaengine_pcm_get_chan (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_dmaengine_pcm_set_config_from_dai_data (struct snd_pcm_substream*,struct snd_dmaengine_dai_dma_data*,struct dma_slave_config*) ; 
 int snd_hwparams_to_dma_slave_config (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

int pxa2xx_pcm_hw_params(struct snd_pcm_substream *substream,
			 struct snd_pcm_hw_params *params)
{
	struct dma_chan *chan = snd_dmaengine_pcm_get_chan(substream);
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_dmaengine_dai_dma_data *dma_params;
	struct dma_slave_config config;
	int ret;

	dma_params = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
	if (!dma_params)
		return 0;

	ret = snd_hwparams_to_dma_slave_config(substream, params, &config);
	if (ret)
		return ret;

	snd_dmaengine_pcm_set_config_from_dai_data(substream,
			snd_soc_dai_get_dma_data(rtd->cpu_dai, substream),
			&config);

	ret = dmaengine_slave_config(chan, &config);
	if (ret)
		return ret;

	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);

	return 0;
}