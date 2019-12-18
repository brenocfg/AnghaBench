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
struct sprd_pcm_dma_private {int hw_chan; struct sprd_pcm_dma_data* data; } ;
struct sprd_pcm_dma_data {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int periods_max; } ;
struct snd_pcm_runtime {TYPE_1__ hw; struct sprd_pcm_dma_private* private_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int SPRD_PCM_DMA_LINKLIST_SIZE ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct sprd_pcm_dma_private*) ; 
 int /*<<< orphan*/  dmam_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct sprd_pcm_dma_private *dma_private = runtime->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct device *dev = component->dev;
	int size = runtime->hw.periods_max * SPRD_PCM_DMA_LINKLIST_SIZE;
	int i;

	for (i = 0; i < dma_private->hw_chan; i++) {
		struct sprd_pcm_dma_data *data = &dma_private->data[i];

		dmam_free_coherent(dev, size, data->virt, data->phys);
	}

	devm_kfree(dev, dma_private);

	return 0;
}