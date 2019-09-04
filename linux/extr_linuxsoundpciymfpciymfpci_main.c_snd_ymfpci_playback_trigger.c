#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_ymfpci_pcm {int running; TYPE_4__** voices; int /*<<< orphan*/  use_441_slot; } ;
struct snd_ymfpci {int /*<<< orphan*/  card; int /*<<< orphan*/  reg_lock; void** ctrl_playback; TYPE_2__* pcm_mixer; int /*<<< orphan*/  pcm; } ;
struct snd_pcm_substream {size_t number; int /*<<< orphan*/  pcm; TYPE_1__* runtime; } ;
struct snd_kcontrol {int /*<<< orphan*/  id; TYPE_3__* vd; } ;
struct TYPE_8__ {int /*<<< orphan*/  number; int /*<<< orphan*/  bank_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  access; } ;
struct TYPE_6__ {struct snd_kcontrol* ctl; } ;
struct TYPE_5__ {struct snd_ymfpci_pcm* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_playback_trigger(struct snd_pcm_substream *substream,
				       int cmd)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_ymfpci_pcm *ypcm = substream->runtime->private_data;
	struct snd_kcontrol *kctl = NULL;
	int result = 0;

	spin_lock(&chip->reg_lock);
	if (ypcm->voices[0] == NULL) {
		result = -EINVAL;
		goto __unlock;
	}
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		chip->ctrl_playback[ypcm->voices[0]->number + 1] = cpu_to_le32(ypcm->voices[0]->bank_addr);
		if (ypcm->voices[1] != NULL && !ypcm->use_441_slot)
			chip->ctrl_playback[ypcm->voices[1]->number + 1] = cpu_to_le32(ypcm->voices[1]->bank_addr);
		ypcm->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (substream->pcm == chip->pcm && !ypcm->use_441_slot) {
			kctl = chip->pcm_mixer[substream->number].ctl;
			kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		}
		/* fall through */
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		chip->ctrl_playback[ypcm->voices[0]->number + 1] = 0;
		if (ypcm->voices[1] != NULL && !ypcm->use_441_slot)
			chip->ctrl_playback[ypcm->voices[1]->number + 1] = 0;
		ypcm->running = 0;
		break;
	default:
		result = -EINVAL;
		break;
	}
      __unlock:
	spin_unlock(&chip->reg_lock);
	if (kctl)
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_INFO, &kctl->id);
	return result;
}