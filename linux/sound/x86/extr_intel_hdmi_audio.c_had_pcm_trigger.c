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
struct snd_pcm_substream {int dummy; } ;
struct snd_intelhad {int need_reset; int /*<<< orphan*/  had_spinlock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 132 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 131 
#define  SNDRV_PCM_TRIGGER_RESUME 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  had_ack_irqs (struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_enable_audio (struct snd_intelhad*,int) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int had_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	int retval = 0;
	struct snd_intelhad *intelhaddata;

	intelhaddata = snd_pcm_substream_chip(substream);

	spin_lock(&intelhaddata->had_spinlock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		/* Enable Audio */
		had_ack_irqs(intelhaddata); /* FIXME: do we need this? */
		had_enable_audio(intelhaddata, true);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* Disable Audio */
		had_enable_audio(intelhaddata, false);
		intelhaddata->need_reset = true;
		break;

	default:
		retval = -EINVAL;
	}
	spin_unlock(&intelhaddata->had_spinlock);
	return retval;
}