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
struct snd_pcm {int /*<<< orphan*/  name; struct snd_als300* private_data; } ;
struct snd_als300 {int /*<<< orphan*/  pci; struct snd_pcm* pcm; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_als300_capture_ops ; 
 int /*<<< orphan*/  snd_als300_playback_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_als300_new_pcm(struct snd_als300 *chip)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(chip->card, "ALS300", 0, 1, 1, &pcm);
	if (err < 0)
		return err;
	pcm->private_data = chip;
	strcpy(pcm->name, "ALS300");
	chip->pcm = pcm;

	/* set operators */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_als300_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_als300_capture_ops);

	/* pre-allocation of buffers */
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
	snd_dma_pci_data(chip->pci), 64*1024, 64*1024);
	return 0;
}