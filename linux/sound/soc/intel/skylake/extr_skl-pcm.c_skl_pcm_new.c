#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_2__* driver; int /*<<< orphan*/  dev; } ;
struct snd_pcm {int dummy; } ;
struct skl_dev {int /*<<< orphan*/  pci; } ;
struct hdac_bus {int dummy; } ;
struct TYPE_6__ {scalar_t__ channels_min; } ;
struct TYPE_4__ {scalar_t__ channels_min; } ;
struct TYPE_5__ {TYPE_1__ capture; TYPE_3__ playback; } ;

/* Variables and functions */
 int CONFIG_SND_HDA_PREALLOC_SIZE ; 
 unsigned int MAX_PREALLOC_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 struct hdac_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int skl_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *dai = rtd->cpu_dai;
	struct hdac_bus *bus = dev_get_drvdata(dai->dev);
	struct snd_pcm *pcm = rtd->pcm;
	unsigned int size;
	struct skl_dev *skl = bus_to_skl(bus);

	if (dai->driver->playback.channels_min ||
		dai->driver->capture.channels_min) {
		/* buffer pre-allocation */
		size = CONFIG_SND_HDA_PREALLOC_SIZE * 1024;
		if (size > MAX_PREALLOC_SIZE)
			size = MAX_PREALLOC_SIZE;
		snd_pcm_lib_preallocate_pages_for_all(pcm,
						SNDRV_DMA_TYPE_DEV_SG,
						snd_dma_pci_data(skl->pci),
						size, MAX_PREALLOC_SIZE);
	}

	return 0;
}