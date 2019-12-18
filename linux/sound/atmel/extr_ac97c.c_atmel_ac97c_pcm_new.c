#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_hardware {int periods_min; int period_bytes_min; int /*<<< orphan*/  buffer_bytes_max; } ;
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct atmel_ac97c* private_data; } ;
struct atmel_ac97c {struct snd_pcm* pcm; TYPE_2__* card; TYPE_1__* pdev; int /*<<< orphan*/  ac97_bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  shortname; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  at91_ac97_pcm_defs ; 
 int /*<<< orphan*/  atmel_ac97_capture_ops ; 
 int /*<<< orphan*/  atmel_ac97_playback_ops ; 
 struct snd_pcm_hardware atmel_ac97c_hw ; 
 int snd_ac97_pcm_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_ac97c_pcm_new(struct atmel_ac97c *chip)
{
	struct snd_pcm		*pcm;
	struct snd_pcm_hardware	hw = atmel_ac97c_hw;
	int			retval;

	retval = snd_ac97_pcm_assign(chip->ac97_bus,
				     ARRAY_SIZE(at91_ac97_pcm_defs),
				     at91_ac97_pcm_defs);
	if (retval)
		return retval;

	retval = snd_pcm_new(chip->card, chip->card->shortname, 0, 1, 1, &pcm);
	if (retval)
		return retval;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &atmel_ac97_capture_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &atmel_ac97_playback_ops);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
			&chip->pdev->dev, hw.periods_min * hw.period_bytes_min,
			hw.buffer_bytes_max);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcm = pcm;

	return 0;
}