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
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_4__ {struct snd_pcm_substream* substream; int /*<<< orphan*/  hw_buf; } ;
struct snd_cs46xx {int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;scalar_t__ accept_valid; TYPE_1__ capt; int /*<<< orphan*/  pci; } ;
struct TYPE_6__ {int /*<<< orphan*/  info; } ;
struct TYPE_5__ {TYPE_3__ hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_MMAP_VALID ; 
 int /*<<< orphan*/  hw_constraints_period_sizes ; 
 TYPE_3__ snd_cs46xx_capture ; 
 scalar_t__ snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 

__attribute__((used)) static int snd_cs46xx_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);

	if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(chip->pci),
				PAGE_SIZE, &chip->capt.hw_buf) < 0)
		return -ENOMEM;
	chip->capt.substream = substream;
	substream->runtime->hw = snd_cs46xx_capture;

	if (chip->accept_valid)
		substream->runtime->hw.info |= SNDRV_PCM_INFO_MMAP_VALID;

	chip->active_ctrl(chip, 1);

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_pcm_hw_constraint_list(substream->runtime, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 
				   &hw_constraints_period_sizes);
#endif
	return 0;
}