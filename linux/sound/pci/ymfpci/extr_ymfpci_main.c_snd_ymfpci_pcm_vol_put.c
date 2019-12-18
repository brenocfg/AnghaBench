#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_ymfpci_pcm {int update_pcm_vol; int /*<<< orphan*/  use_441_slot; } ;
struct snd_ymfpci {int /*<<< orphan*/  voice_lock; TYPE_4__* pcm_mixer; } ;
struct snd_pcm_substream {TYPE_5__* runtime; } ;
struct TYPE_6__ {unsigned int subdevice; } ;
struct snd_kcontrol {scalar_t__ private_value; TYPE_1__ id; } ;
struct TYPE_7__ {int* value; } ;
struct TYPE_8__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_10__ {struct snd_ymfpci_pcm* private_data; } ;
struct TYPE_9__ {int left; int right; } ;

/* Variables and functions */
 struct snd_ymfpci* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ymfpci_pcm_vol_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	unsigned int subs = kcontrol->id.subdevice;
	struct snd_pcm_substream *substream;
	unsigned long flags;

	if (ucontrol->value.integer.value[0] != chip->pcm_mixer[subs].left ||
	    ucontrol->value.integer.value[1] != chip->pcm_mixer[subs].right) {
		chip->pcm_mixer[subs].left = ucontrol->value.integer.value[0];
		chip->pcm_mixer[subs].right = ucontrol->value.integer.value[1];
		if (chip->pcm_mixer[subs].left > 0x8000)
			chip->pcm_mixer[subs].left = 0x8000;
		if (chip->pcm_mixer[subs].right > 0x8000)
			chip->pcm_mixer[subs].right = 0x8000;

		substream = (struct snd_pcm_substream *)kcontrol->private_value;
		spin_lock_irqsave(&chip->voice_lock, flags);
		if (substream->runtime && substream->runtime->private_data) {
			struct snd_ymfpci_pcm *ypcm = substream->runtime->private_data;
			if (!ypcm->use_441_slot)
				ypcm->update_pcm_vol = 2;
		}
		spin_unlock_irqrestore(&chip->voice_lock, flags);
		return 1;
	}
	return 0;
}