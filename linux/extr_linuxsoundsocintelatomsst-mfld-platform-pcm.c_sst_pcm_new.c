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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; struct snd_pcm* pcm; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_3__* driver; } ;
struct snd_pcm {int dummy; } ;
struct TYPE_5__ {scalar_t__ channels_min; } ;
struct TYPE_4__ {scalar_t__ channels_min; } ;
struct TYPE_6__ {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  SST_MAX_BUFFER ; 
 int /*<<< orphan*/  SST_MIN_BUFFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_dma_continuous_data (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *dai = rtd->cpu_dai;
	struct snd_pcm *pcm = rtd->pcm;
	int retval = 0;

	if (dai->driver->playback.channels_min ||
			dai->driver->capture.channels_min) {
		retval =  snd_pcm_lib_preallocate_pages_for_all(pcm,
			SNDRV_DMA_TYPE_CONTINUOUS,
			snd_dma_continuous_data(GFP_DMA),
			SST_MIN_BUFFER, SST_MAX_BUFFER);
		if (retval) {
			dev_err(rtd->dev, "dma buffer allocation failure\n");
			return retval;
		}
	}
	return retval;
}