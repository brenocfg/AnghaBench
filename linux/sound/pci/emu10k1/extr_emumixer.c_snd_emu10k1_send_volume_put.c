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
struct snd_kcontrol {int dummy; } ;
struct snd_emu10k1_pcm_mixer {int** send_volume; TYPE_4__* epcm; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; scalar_t__ audigy; struct snd_emu10k1_pcm_mixer* pcm_mixer; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_3__** voices; } ;
struct TYPE_7__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 size_t snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_emu10k1_send_volume (struct snd_emu10k1*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int snd_emu10k1_send_volume_put(struct snd_kcontrol *kcontrol,
                                       struct snd_ctl_elem_value *ucontrol)
{
	unsigned long flags;
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	struct snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	int change = 0, idx, val;
	int num_efx = emu->audigy ? 8 : 4;

	spin_lock_irqsave(&emu->reg_lock, flags);
	for (idx = 0; idx < 3*num_efx; idx++) {
		val = ucontrol->value.integer.value[idx] & 255;
		if (mix->send_volume[idx/num_efx][idx%num_efx] != val) {
			mix->send_volume[idx/num_efx][idx%num_efx] = val;
			change = 1;
		}
	}
	if (change && mix->epcm) {
		if (mix->epcm->voices[0] && mix->epcm->voices[1]) {
			update_emu10k1_send_volume(emu, mix->epcm->voices[0]->number,
						   &mix->send_volume[1][0]);
			update_emu10k1_send_volume(emu, mix->epcm->voices[1]->number,
						   &mix->send_volume[2][0]);
		} else if (mix->epcm->voices[0]) {
			update_emu10k1_send_volume(emu, mix->epcm->voices[0]->number,
						   &mix->send_volume[0][0]);
		}
	}
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return change;
}