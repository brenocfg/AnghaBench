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
struct snd_pcm_substream {int dummy; } ;
struct oxygen {int pcm_active; int /*<<< orphan*/ ** streams; int /*<<< orphan*/  mutex; TYPE_2__** controls; int /*<<< orphan*/  card; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; TYPE_1__* vd; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 size_t CONTROL_SPDIF_PCM ; 
 unsigned int PCM_MULTICH ; 
 unsigned int PCM_SPDIF ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int SNDRV_CTL_EVENT_MASK_INFO ; 
 int SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int oxygen_substream_channel (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  oxygen_update_spdif_source (struct oxygen*) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct oxygen* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int oxygen_close(struct snd_pcm_substream *substream)
{
	struct oxygen *chip = snd_pcm_substream_chip(substream);
	unsigned int channel = oxygen_substream_channel(substream);

	mutex_lock(&chip->mutex);
	chip->pcm_active &= ~(1 << channel);
	if (channel == PCM_SPDIF) {
		chip->controls[CONTROL_SPDIF_PCM]->vd[0].access |=
			SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &chip->controls[CONTROL_SPDIF_PCM]->id);
	}
	if (channel == PCM_SPDIF || channel == PCM_MULTICH)
		oxygen_update_spdif_source(chip);
	mutex_unlock(&chip->mutex);

	chip->streams[channel] = NULL;
	return 0;
}