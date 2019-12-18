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
struct snd_pcm {int /*<<< orphan*/  name; int /*<<< orphan*/  info_flags; struct snd_ad1816a* private_data; } ;
struct snd_ad1816a {int dma1; int dma2; struct snd_pcm* pcm; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_ad1816a_capture_ops ; 
 int /*<<< orphan*/  snd_ad1816a_chip_id (struct snd_ad1816a*) ; 
 int /*<<< orphan*/  snd_ad1816a_init (struct snd_ad1816a*) ; 
 int /*<<< orphan*/  snd_ad1816a_playback_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_ad1816a_pcm(struct snd_ad1816a *chip, int device)
{
	int error;
	struct snd_pcm *pcm;

	if ((error = snd_pcm_new(chip->card, "AD1816A", device, 1, 1, &pcm)))
		return error;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ad1816a_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ad1816a_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = (chip->dma1 == chip->dma2 ) ? SNDRV_PCM_INFO_JOINT_DUPLEX : 0;

	strcpy(pcm->name, snd_ad1816a_chip_id(chip));
	snd_ad1816a_init(chip);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      chip->card->dev,
					      64*1024, chip->dma1 > 3 || chip->dma2 > 3 ? 128*1024 : 64*1024);

	chip->pcm = pcm;
	return 0;
}