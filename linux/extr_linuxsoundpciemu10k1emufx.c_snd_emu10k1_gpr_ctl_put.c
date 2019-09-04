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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_emu10k1_fx8010_ctl {unsigned int vcount; unsigned int min; unsigned int max; unsigned int* value; int translation; int count; scalar_t__* gpr; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; scalar_t__ gpr_base; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EIO ; 
#define  EMU10K1_GPR_TRANSLATION_BASS 132 
#define  EMU10K1_GPR_TRANSLATION_NONE 131 
#define  EMU10K1_GPR_TRANSLATION_ONOFF 130 
#define  EMU10K1_GPR_TRANSLATION_TABLE100 129 
#define  EMU10K1_GPR_TRANSLATION_TREBLE 128 
 unsigned int** bass_table ; 
 unsigned int* db_table ; 
 unsigned int* onoff_table ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int** treble_table ; 

__attribute__((used)) static int snd_emu10k1_gpr_ctl_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	struct snd_emu10k1_fx8010_ctl *ctl =
		(struct snd_emu10k1_fx8010_ctl *) kcontrol->private_value;
	unsigned long flags;
	unsigned int nval, val;
	unsigned int i, j;
	int change = 0;
	
	spin_lock_irqsave(&emu->reg_lock, flags);
	for (i = 0; i < ctl->vcount; i++) {
		nval = ucontrol->value.integer.value[i];
		if (nval < ctl->min)
			nval = ctl->min;
		if (nval > ctl->max)
			nval = ctl->max;
		if (nval != ctl->value[i])
			change = 1;
		val = ctl->value[i] = nval;
		switch (ctl->translation) {
		case EMU10K1_GPR_TRANSLATION_NONE:
			snd_emu10k1_ptr_write(emu, emu->gpr_base + ctl->gpr[i], 0, val);
			break;
		case EMU10K1_GPR_TRANSLATION_TABLE100:
			snd_emu10k1_ptr_write(emu, emu->gpr_base + ctl->gpr[i], 0, db_table[val]);
			break;
		case EMU10K1_GPR_TRANSLATION_BASS:
			if ((ctl->count % 5) != 0 || (ctl->count / 5) != ctl->vcount) {
				change = -EIO;
				goto __error;
			}
			for (j = 0; j < 5; j++)
				snd_emu10k1_ptr_write(emu, emu->gpr_base + ctl->gpr[j * ctl->vcount + i], 0, bass_table[val][j]);
			break;
		case EMU10K1_GPR_TRANSLATION_TREBLE:
			if ((ctl->count % 5) != 0 || (ctl->count / 5) != ctl->vcount) {
				change = -EIO;
				goto __error;
			}
			for (j = 0; j < 5; j++)
				snd_emu10k1_ptr_write(emu, emu->gpr_base + ctl->gpr[j * ctl->vcount + i], 0, treble_table[val][j]);
			break;
		case EMU10K1_GPR_TRANSLATION_ONOFF:
			snd_emu10k1_ptr_write(emu, emu->gpr_base + ctl->gpr[i], 0, onoff_table[val]);
			break;
		}
	}
      __error:
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return change;
}