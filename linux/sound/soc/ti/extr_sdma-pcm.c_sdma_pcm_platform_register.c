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
struct snd_dmaengine_pcm_config {char** chan_names; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX ; 
 struct snd_dmaengine_pcm_config* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (struct device*,struct snd_dmaengine_pcm_config*,unsigned int) ; 
 struct snd_dmaengine_pcm_config sdma_dmaengine_pcm_config ; 

int sdma_pcm_platform_register(struct device *dev,
			       char *txdmachan, char *rxdmachan)
{
	struct snd_dmaengine_pcm_config *config;
	unsigned int flags = 0;

	/* Standard names for the directions: 'tx' and 'rx' */
	if (!txdmachan && !rxdmachan)
		return devm_snd_dmaengine_pcm_register(dev,
						&sdma_dmaengine_pcm_config, 0);

	config = devm_kzalloc(dev, sizeof(*config), GFP_KERNEL);
	if (!config)
		return -ENOMEM;

	*config = sdma_dmaengine_pcm_config;

	if (!txdmachan || !rxdmachan) {
		/* One direction only PCM */
		flags |= SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX;
		if (!txdmachan) {
			txdmachan = rxdmachan;
			rxdmachan = NULL;
		}
	}

	config->chan_names[0] = txdmachan;
	config->chan_names[1] = rxdmachan;

	return devm_snd_dmaengine_pcm_register(dev, config, flags);
}