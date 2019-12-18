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
struct snd_emu8000 {unsigned short treble_level; unsigned short bass_level; int /*<<< orphan*/  control_lock; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emu8000_update_equalizer (struct snd_emu8000*) ; 
 struct snd_emu8000* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mixer_bass_treble_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int change;
	unsigned short val1;
	
	val1 = ucontrol->value.integer.value[0] % 12;
	spin_lock_irqsave(&emu->control_lock, flags);
	if (kcontrol->private_value) {
		change = val1 != emu->treble_level;
		emu->treble_level = val1;
	} else {
		change = val1 != emu->bass_level;
		emu->bass_level = val1;
	}
	spin_unlock_irqrestore(&emu->control_lock, flags);
	snd_emu8000_update_equalizer(emu);
	return change;
}