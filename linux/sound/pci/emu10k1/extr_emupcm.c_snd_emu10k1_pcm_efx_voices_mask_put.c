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
struct snd_emu10k1 {unsigned int* efx_voices_mask; int /*<<< orphan*/  reg_lock; scalar_t__ audigy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_pcm_efx_voices_mask_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int nval[2], bits;
	int nefx = emu->audigy ? 64 : 32;
	int nefxb = emu->audigy ? 7 : 6;
	int change, idx;
	
	nval[0] = nval[1] = 0;
	for (idx = 0, bits = 0; idx < nefx; idx++)
		if (ucontrol->value.integer.value[idx]) {
			nval[idx / 32] |= 1 << (idx % 32);
			bits++;
		}
		
	for (idx = 0; idx < nefxb; idx++)
		if (1 << idx == bits)
			break;
	
	if (idx >= nefxb)
		return -EINVAL;

	spin_lock_irq(&emu->reg_lock);
	change = (nval[0] != emu->efx_voices_mask[0]) ||
		(nval[1] != emu->efx_voices_mask[1]);
	emu->efx_voices_mask[0] = nval[0];
	emu->efx_voices_mask[1] = nval[1];
	spin_unlock_irq(&emu->reg_lock);
	return change;
}