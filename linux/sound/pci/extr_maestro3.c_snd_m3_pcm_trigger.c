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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_m3 {int /*<<< orphan*/  reg_lock; } ;
struct m3_dma {int running; } ;
struct TYPE_2__ {struct m3_dma* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_m3_pcm_start (struct snd_m3*,struct m3_dma*,struct snd_pcm_substream*) ; 
 int snd_m3_pcm_stop (struct snd_m3*,struct m3_dma*,struct snd_pcm_substream*) ; 
 struct snd_m3* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_m3_pcm_trigger(struct snd_pcm_substream *subs, int cmd)
{
	struct snd_m3 *chip = snd_pcm_substream_chip(subs);
	struct m3_dma *s = subs->runtime->private_data;
	int err = -EINVAL;

	if (snd_BUG_ON(!s))
		return -ENXIO;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (s->running)
			err = -EBUSY;
		else {
			s->running = 1;
			err = snd_m3_pcm_start(chip, s, subs);
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (! s->running)
			err = 0; /* should return error? */
		else {
			s->running = 0;
			err = snd_m3_pcm_stop(chip, s, subs);
		}
		break;
	}
	spin_unlock(&chip->reg_lock);
	return err;
}