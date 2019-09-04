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
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_m3* private_data; } ;
struct snd_m3 {int /*<<< orphan*/  pci; struct snd_pcm* pcm; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CAPTURES ; 
 int /*<<< orphan*/  MAX_PLAYBACKS ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_capture_ops ; 
 int /*<<< orphan*/  snd_m3_playback_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_m3_pcm(struct snd_m3 * chip, int device)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(chip->card, chip->card->driver, device,
			  MAX_PLAYBACKS, MAX_CAPTURES, &pcm);
	if (err < 0)
		return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_m3_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_m3_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->driver);
	chip->pcm = pcm;
	
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci), 64*1024, 64*1024);

	return 0;
}