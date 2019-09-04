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
struct snd_dmaengine_dai_dma_data {int /*<<< orphan*/  addr_width; int /*<<< orphan*/  addr; } ;
struct dma_slave_config {int src_maxburst; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  src_addr; } ;

/* Variables and functions */
 int params_channels (struct snd_pcm_hw_params*) ; 
 int snd_hwparams_to_dma_slave_config (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct dma_slave_config*) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int img_i2s_in_dma_prepare_slave_config(struct snd_pcm_substream *st,
	struct snd_pcm_hw_params *params, struct dma_slave_config *sc)
{
	unsigned int i2s_channels = params_channels(params) / 2;
	struct snd_soc_pcm_runtime *rtd = st->private_data;
	struct snd_dmaengine_dai_dma_data *dma_data;
	int ret;

	dma_data = snd_soc_dai_get_dma_data(rtd->cpu_dai, st);

	ret = snd_hwparams_to_dma_slave_config(st, params, sc);
	if (ret)
		return ret;

	sc->src_addr = dma_data->addr;
	sc->src_addr_width = dma_data->addr_width;
	sc->src_maxburst = 4 * i2s_channels;

	return 0;
}