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
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; TYPE_3__* card; } ;
struct snd_pcm {TYPE_2__* streams; } ;
struct snd_card {TYPE_1__* dev; } ;
struct TYPE_6__ {struct snd_card* snd_card; } ;
struct TYPE_5__ {scalar_t__ substream; } ;
struct TYPE_4__ {scalar_t__ coherent_dma_mask; int /*<<< orphan*/ * dma_mask; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  cygnus_dma_dmamask ; 
 int /*<<< orphan*/  cygnus_dma_free_dma_buffers (struct snd_pcm*) ; 
 int cygnus_pcm_preallocate_dma_buffer (struct snd_pcm*,size_t) ; 

__attribute__((used)) static int cygnus_dma_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm *pcm = rtd->pcm;
	int ret;

	if (!card->dev->dma_mask)
		card->dev->dma_mask = &cygnus_dma_dmamask;
	if (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = DMA_BIT_MASK(32);

	if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) {
		ret = cygnus_pcm_preallocate_dma_buffer(pcm,
				SNDRV_PCM_STREAM_PLAYBACK);
		if (ret)
			return ret;
	}

	if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) {
		ret = cygnus_pcm_preallocate_dma_buffer(pcm,
				SNDRV_PCM_STREAM_CAPTURE);
		if (ret) {
			cygnus_dma_free_dma_buffers(pcm);
			return ret;
		}
	}

	return 0;
}