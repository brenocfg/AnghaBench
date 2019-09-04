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
struct snd_soc_component {int dummy; } ;
struct dmaengine_pcm {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_DMAENGINE_PCM_DRV_NAME ; 
 int /*<<< orphan*/  dmaengine_pcm_release_chan (struct dmaengine_pcm*) ; 
 int /*<<< orphan*/  kfree (struct dmaengine_pcm*) ; 
 struct snd_soc_component* snd_soc_lookup_component (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (struct device*) ; 
 struct dmaengine_pcm* soc_component_to_pcm (struct snd_soc_component*) ; 

void snd_dmaengine_pcm_unregister(struct device *dev)
{
	struct snd_soc_component *component;
	struct dmaengine_pcm *pcm;

	component = snd_soc_lookup_component(dev, SND_DMAENGINE_PCM_DRV_NAME);
	if (!component)
		return;

	pcm = soc_component_to_pcm(component);

	snd_soc_unregister_component(dev);
	dmaengine_pcm_release_chan(pcm);
	kfree(pcm);
}