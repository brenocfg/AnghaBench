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
struct snd_pcm {int /*<<< orphan*/  private_free; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_pcm* pxa2xx_ac97_pcm ; 
 int /*<<< orphan*/  pxa2xx_ac97_pcm_ops ; 
 int /*<<< orphan*/  pxa2xx_pcm_free_dma_buffers ; 
 int pxa2xx_pcm_preallocate_dma_buffer (struct snd_pcm*,int) ; 
 int snd_pcm_new (struct snd_card*,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa2xx_ac97_pcm_new(struct snd_card *card)
{
	struct snd_pcm *pcm;
	int stream, ret;

	ret = snd_pcm_new(card, "PXA2xx-PCM", 0, 1, 1, &pcm);
	if (ret)
		goto out;

	pcm->private_free = pxa2xx_pcm_free_dma_buffers;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	if (ret)
		goto out;

	stream = SNDRV_PCM_STREAM_PLAYBACK;
	snd_pcm_set_ops(pcm, stream, &pxa2xx_ac97_pcm_ops);
	ret = pxa2xx_pcm_preallocate_dma_buffer(pcm, stream);
	if (ret)
		goto out;

	stream = SNDRV_PCM_STREAM_CAPTURE;
	snd_pcm_set_ops(pcm, stream, &pxa2xx_ac97_pcm_ops);
	ret = pxa2xx_pcm_preallocate_dma_buffer(pcm, stream);
	if (ret)
		goto out;

	pxa2xx_ac97_pcm = pcm;
	ret = 0;

 out:
	return ret;
}