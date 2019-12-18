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
struct snd_kcontrol {int dummy; } ;
struct snd_emu10k1_pcm_mixer {int /*<<< orphan*/ ** send_volume; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; scalar_t__ audigy; struct snd_emu10k1_pcm_mixer* efx_pcm_mixer; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1_efx_send_volume_get(struct snd_kcontrol *kcontrol,
                                       struct snd_ctl_elem_value *ucontrol)
{
	unsigned long flags;
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	struct snd_emu10k1_pcm_mixer *mix =
		&emu->efx_pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	int idx;
	int num_efx = emu->audigy ? 8 : 4;

	spin_lock_irqsave(&emu->reg_lock, flags);
	for (idx = 0; idx < num_efx; idx++)
		ucontrol->value.integer.value[idx] = mix->send_volume[0][idx];
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return 0;
}