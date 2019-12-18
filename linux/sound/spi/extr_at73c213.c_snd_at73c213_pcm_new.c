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
struct snd_pcm {int /*<<< orphan*/  name; int /*<<< orphan*/  info_flags; struct snd_at73c213* private_data; } ;
struct snd_at73c213 {TYPE_2__* ssc; struct snd_pcm* pcm; TYPE_3__* card; } ;
struct TYPE_6__ {int /*<<< orphan*/  shortname; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_BLOCK_TRANSFER ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  at73c213_playback_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int snd_pcm_new (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_at73c213_pcm_new(struct snd_at73c213 *chip, int device)
{
	struct snd_pcm *pcm;
	int retval;

	retval = snd_pcm_new(chip->card, chip->card->shortname,
			device, 1, 0, &pcm);
	if (retval < 0)
		goto out;

	pcm->private_data = chip;
	pcm->info_flags = SNDRV_PCM_INFO_BLOCK_TRANSFER;
	strcpy(pcm->name, "at73c213");
	chip->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &at73c213_playback_ops);

	snd_pcm_lib_preallocate_pages_for_all(chip->pcm,
			SNDRV_DMA_TYPE_DEV, &chip->ssc->pdev->dev,
			64 * 1024, 64 * 1024);
out:
	return retval;
}