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
struct snd_dmaengine_pcm_config {char** chan_names; int /*<<< orphan*/  dma_dev; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int snd_dmaengine_pcm_register (struct device*,struct snd_dmaengine_pcm_config*,int /*<<< orphan*/ ) ; 
 struct snd_dmaengine_pcm_config tegra_dmaengine_pcm_config ; 

int tegra_pcm_platform_register_with_chan_names(struct device *dev,
				struct snd_dmaengine_pcm_config *config,
				char *txdmachan, char *rxdmachan)
{
	*config = tegra_dmaengine_pcm_config;
	config->dma_dev = dev->parent;
	config->chan_names[0] = txdmachan;
	config->chan_names[1] = rxdmachan;

	return snd_dmaengine_pcm_register(dev, config, 0);
}