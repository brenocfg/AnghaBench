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
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_ad1889* private_data; } ;
struct snd_ad1889 {TYPE_1__* card; int /*<<< orphan*/  pci; int /*<<< orphan*/ * csubs; int /*<<< orphan*/ * psubs; struct snd_pcm* pcm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int BUFFER_BYTES_MAX ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_ad1889_capture_ops ; 
 int /*<<< orphan*/  snd_ad1889_playback_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_ad1889_pcm_init(struct snd_ad1889 *chip, int device)
{
	int err;
	struct snd_pcm *pcm;

	err = snd_pcm_new(chip->card, chip->card->driver, device, 1, 1, &pcm);
	if (err < 0)
		return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, 
			&snd_ad1889_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_ad1889_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->shortname);
	
	chip->pcm = pcm;
	chip->psubs = NULL;
	chip->csubs = NULL;

	err = snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						snd_dma_pci_data(chip->pci),
						BUFFER_BYTES_MAX / 2,
						BUFFER_BYTES_MAX);

	if (err < 0) {
		dev_err(chip->card->dev, "buffer allocation error: %d\n", err);
		return err;
	}
	
	return 0;
}