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
struct snd_dmaengine_pcm_config {scalar_t__ process; } ;
struct TYPE_2__ {char* debugfs_prefix; } ;
struct dmaengine_pcm {unsigned int flags; TYPE_1__ component; struct snd_dmaengine_pcm_config const* config; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dmaengine_pcm_component ; 
 int /*<<< orphan*/  dmaengine_pcm_component_process ; 
 int /*<<< orphan*/  dmaengine_pcm_release_chan (struct dmaengine_pcm*) ; 
 int dmaengine_pcm_request_chan_of (struct dmaengine_pcm*,struct device*,struct snd_dmaengine_pcm_config const*) ; 
 int /*<<< orphan*/  kfree (struct dmaengine_pcm*) ; 
 struct dmaengine_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component (struct device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_dmaengine_pcm_register(struct device *dev,
	const struct snd_dmaengine_pcm_config *config, unsigned int flags)
{
	struct dmaengine_pcm *pcm;
	int ret;

	pcm = kzalloc(sizeof(*pcm), GFP_KERNEL);
	if (!pcm)
		return -ENOMEM;

#ifdef CONFIG_DEBUG_FS
	pcm->component.debugfs_prefix = "dma";
#endif
	pcm->config = config;
	pcm->flags = flags;

	ret = dmaengine_pcm_request_chan_of(pcm, dev, config);
	if (ret)
		goto err_free_dma;

	if (config && config->process)
		ret = snd_soc_add_component(dev, &pcm->component,
					    &dmaengine_pcm_component_process,
					    NULL, 0);
	else
		ret = snd_soc_add_component(dev, &pcm->component,
					    &dmaengine_pcm_component, NULL, 0);
	if (ret)
		goto err_free_dma;

	return 0;

err_free_dma:
	dmaengine_pcm_release_chan(pcm);
	kfree(pcm);
	return ret;
}