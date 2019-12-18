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
struct snd_wm8776 {unsigned int** volumes; } ;
struct snd_maya44 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ice; struct snd_wm8776* wm; } ;
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;
struct maya_vol_info {unsigned int maxval; unsigned int mute; unsigned int offset; unsigned int update; int mask; int* mux_bits; int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8776_REG_ADC_MUX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t snd_ctl_get_ioff (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_maya44* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct maya_vol_info* vol_info ; 
 int wm8776_write_bits (int /*<<< orphan*/ ,struct snd_wm8776*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int maya_vol_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	struct snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	unsigned int idx = kcontrol->private_value;
	struct maya_vol_info *vol = &vol_info[idx];
	unsigned int val, data;
	int ch, changed = 0;

	mutex_lock(&chip->mutex);
	for (ch = 0; ch < 2; ch++) {
		val = ucontrol->value.integer.value[ch];
		if (val > vol->maxval)
			val = vol->maxval;
		if (val == wm->volumes[idx][ch])
			continue;
		if (!val)
			data = vol->mute;
		else
			data = (val - 1) + vol->offset;
		data |= vol->update;
		changed |= wm8776_write_bits(chip->ice, wm, vol->regs[ch],
					     vol->mask | vol->update, data);
		if (vol->mux_bits[ch])
			wm8776_write_bits(chip->ice, wm, WM8776_REG_ADC_MUX,
					  vol->mux_bits[ch],
					  val ? 0 : vol->mux_bits[ch]);
		wm->volumes[idx][ch] = val;
	}
	mutex_unlock(&chip->mutex);
	return changed;
}