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
struct snd_sb {int version; int dma8; scalar_t__ dma16; struct snd_card* card; } ;
struct snd_pcm {struct snd_sb* private_data; int /*<<< orphan*/  info_flags; int /*<<< orphan*/  name; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_HALF_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 int snd_pcm_new (struct snd_card*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sb8_capture_ops ; 
 int /*<<< orphan*/  snd_sb8_playback_ops ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 

int snd_sb8dsp_pcm(struct snd_sb *chip, int device)
{
	struct snd_card *card = chip->card;
	struct snd_pcm *pcm;
	int err;
	size_t max_prealloc = 64 * 1024;

	if ((err = snd_pcm_new(card, "SB8 DSP", device, 1, 1, &pcm)) < 0)
		return err;
	sprintf(pcm->name, "DSP v%i.%i", chip->version >> 8, chip->version & 0xff);
	pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
	pcm->private_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_sb8_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_sb8_capture_ops);

	if (chip->dma8 > 3 || chip->dma16 >= 0)
		max_prealloc = 128 * 1024;
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      card->dev,
					      64*1024, max_prealloc);

	return 0;
}