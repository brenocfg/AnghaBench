#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcsp {TYPE_1__* pcm; int /*<<< orphan*/  card; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  info_flags; struct snd_pcsp* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCSP_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_HALF_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_dma_continuous_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcsp_playback_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_pcsp_new_pcm(struct snd_pcsp *chip)
{
	int err;

	err = snd_pcm_new(chip->card, "pcspeaker", 0, 1, 0, &chip->pcm);
	if (err < 0)
		return err;

	snd_pcm_set_ops(chip->pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_pcsp_playback_ops);

	chip->pcm->private_data = chip;
	chip->pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
	strcpy(chip->pcm->name, "pcsp");

	snd_pcm_lib_preallocate_pages_for_all(chip->pcm,
					      SNDRV_DMA_TYPE_CONTINUOUS,
					      snd_dma_continuous_data
					      (GFP_KERNEL), PCSP_BUFFER_SIZE,
					      PCSP_BUFFER_SIZE);

	return 0;
}