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
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; TYPE_1__* card; } ;
struct snd_pcm {int dummy; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nuc900_dma_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm *pcm = rtd->pcm;
	int ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
		card->dev, 4 * 1024, (4 * 1024) - 1);

	return 0;
}