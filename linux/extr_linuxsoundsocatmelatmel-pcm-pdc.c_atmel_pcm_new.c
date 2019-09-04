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
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; TYPE_1__* card; } ;
struct snd_pcm {TYPE_2__* streams; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ substream; } ;
struct TYPE_3__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int atmel_pcm_preallocate_dma_buffer (struct snd_pcm*,size_t) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int atmel_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm *pcm = rtd->pcm;
	int ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) {
		pr_debug("atmel-pcm: allocating PCM playback DMA buffer\n");
		ret = atmel_pcm_preallocate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_PLAYBACK);
		if (ret)
			goto out;
	}

	if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) {
		pr_debug("atmel-pcm: allocating PCM capture DMA buffer\n");
		ret = atmel_pcm_preallocate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_CAPTURE);
		if (ret)
			goto out;
	}
 out:
	return ret;
}