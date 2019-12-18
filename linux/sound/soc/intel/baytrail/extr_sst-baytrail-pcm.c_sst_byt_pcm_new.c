#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_pdata {int /*<<< orphan*/  dma_dev; } ;
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm {TYPE_1__* streams; } ;
struct TYPE_4__ {size_t buffer_bytes_max; } ;
struct TYPE_3__ {scalar_t__ substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 struct sst_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 TYPE_2__ sst_byt_pcm_hardware ; 

__attribute__((used)) static int sst_byt_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_pcm *pcm = rtd->pcm;
	size_t size;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_pdata *pdata = dev_get_platdata(component->dev);

	if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream ||
	    pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) {
		size = sst_byt_pcm_hardware.buffer_bytes_max;
		snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						      pdata->dma_dev,
						      size, size);
	}

	return 0;
}