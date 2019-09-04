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
struct snd_dmaengine_pcm_config {int (* compat_filter_fn ) (struct dma_chan*,void*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int SND_DMAENGINE_PCM_FLAG_COMPAT ; 
 int SND_DMAENGINE_PCM_FLAG_NO_DT ; 
 int devm_snd_dmaengine_pcm_register (struct device*,struct snd_dmaengine_pcm_config*,int) ; 
 struct snd_dmaengine_pcm_config spear_dmaengine_pcm_config ; 

int devm_spear_pcm_platform_register(struct device *dev,
			struct snd_dmaengine_pcm_config *config,
			bool (*filter)(struct dma_chan *chan, void *slave))
{
	*config = spear_dmaengine_pcm_config;
	config->compat_filter_fn = filter;

	return devm_snd_dmaengine_pcm_register(dev, config,
		SND_DMAENGINE_PCM_FLAG_NO_DT |
		SND_DMAENGINE_PCM_FLAG_COMPAT);
}