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
struct snd_pcm {char* name; int /*<<< orphan*/  info_flags; struct snd_es18xx* private_data; } ;
struct snd_es18xx {int version; int caps; int dma1; int dma2; struct snd_pcm* pcm; } ;
struct snd_card {int /*<<< orphan*/  dev; struct snd_es18xx* private_data; } ;

/* Variables and functions */
 int ES18XX_DUPLEX_SAME ; 
 int ES18XX_PCM2 ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_HALF_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_es18xx_capture_ops ; 
 int /*<<< orphan*/  snd_es18xx_playback_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (struct snd_card*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int snd_es18xx_pcm(struct snd_card *card, int device)
{
	struct snd_es18xx *chip = card->private_data;
        struct snd_pcm *pcm;
	char str[16];
	int err;

	sprintf(str, "ES%x", chip->version);
	if (chip->caps & ES18XX_PCM2)
		err = snd_pcm_new(card, str, device, 2, 1, &pcm);
	else
		err = snd_pcm_new(card, str, device, 1, 1, &pcm);
        if (err < 0)
                return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_es18xx_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_es18xx_capture_ops);

	/* global setup */
        pcm->private_data = chip;
        pcm->info_flags = 0;
	if (chip->caps & ES18XX_DUPLEX_SAME)
		pcm->info_flags |= SNDRV_PCM_INFO_JOINT_DUPLEX;
	if (! (chip->caps & ES18XX_PCM2))
		pcm->info_flags |= SNDRV_PCM_INFO_HALF_DUPLEX;
	sprintf(pcm->name, "ESS AudioDrive ES%x", chip->version);
        chip->pcm = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      card->dev,
					      64*1024,
					      chip->dma1 > 3 || chip->dma2 > 3 ? 128*1024 : 64*1024);
	return 0;
}