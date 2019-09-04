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
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_azf3328* private_data; } ;
struct snd_azf3328 {int /*<<< orphan*/  pci; struct snd_pcm** pcm; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 size_t AZF_CODEC_CAPTURE ; 
 size_t AZF_CODEC_I2S_OUT ; 
 size_t AZF_CODEC_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_azf3328_capture_ops ; 
 int /*<<< orphan*/  snd_azf3328_i2s_out_ops ; 
 int /*<<< orphan*/  snd_azf3328_playback_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_azf3328_pcm(struct snd_azf3328 *chip)
{
	/* pcm devices */
	enum { AZF_PCMDEV_STD, AZF_PCMDEV_I2S_OUT, NUM_AZF_PCMDEVS };

	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(chip->card, "AZF3328 DSP", AZF_PCMDEV_STD,
								1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
						&snd_azf3328_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
						&snd_azf3328_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->shortname);
	/* same pcm object for playback/capture (see snd_pcm_new() above) */
	chip->pcm[AZF_CODEC_PLAYBACK] = pcm;
	chip->pcm[AZF_CODEC_CAPTURE] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						snd_dma_pci_data(chip->pci),
							64*1024, 64*1024);

	err = snd_pcm_new(chip->card, "AZF3328 I2S OUT", AZF_PCMDEV_I2S_OUT,
								1, 0, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
						&snd_azf3328_i2s_out_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcm[AZF_CODEC_I2S_OUT] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						snd_dma_pci_data(chip->pci),
							64*1024, 64*1024);

	return 0;
}