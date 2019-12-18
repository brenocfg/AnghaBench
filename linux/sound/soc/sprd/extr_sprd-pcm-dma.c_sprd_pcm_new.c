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
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; TYPE_1__* card; } ;
struct snd_pcm_substream {int /*<<< orphan*/  dma_buffer; } ;
struct snd_pcm {TYPE_2__* streams; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer_bytes_max; } ;
struct TYPE_5__ {struct snd_pcm_substream* substream; } ;
struct TYPE_4__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 
 TYPE_3__ sprd_pcm_hardware ; 

__attribute__((used)) static int sprd_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm *pcm = rtd->pcm;
	struct snd_pcm_substream *substream;
	int ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	if (substream) {
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, card->dev,
					  sprd_pcm_hardware.buffer_bytes_max,
					  &substream->dma_buffer);
		if (ret) {
			dev_err(card->dev,
				"can't alloc playback dma buffer: %d\n", ret);
			return ret;
		}
	}

	substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	if (substream) {
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, card->dev,
					  sprd_pcm_hardware.buffer_bytes_max,
					  &substream->dma_buffer);
		if (ret) {
			dev_err(card->dev,
				"can't alloc capture dma buffer: %d\n", ret);
			snd_dma_free_pages(&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->dma_buffer);
			return ret;
		}
	}

	return 0;
}