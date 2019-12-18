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
struct soc_mixer_control {int reg; unsigned int shift; int max; unsigned int invert; int rreg; unsigned int rshift; } ;
struct snd_soc_dapm_context {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm_mutex; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_CLASS_RUNTIME ; 
 int SND_SOC_NOPM ; 
 unsigned int dapm_kcontrol_get_value (struct snd_kcontrol*) ; 
 scalar_t__ dapm_kcontrol_is_powered (struct snd_kcontrol*) ; 
 int fls (int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 scalar_t__ snd_soc_volsw_is_stereo (struct soc_mixer_control*) ; 
 int soc_dapm_read (struct snd_soc_dapm_context*,int,unsigned int*) ; 

int snd_soc_dapm_get_volsw(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct snd_soc_card *card = dapm->card;
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	int reg = mc->reg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	unsigned int width = fls(max);
	unsigned int mask = (1 << fls(max)) - 1;
	unsigned int invert = mc->invert;
	unsigned int reg_val, val, rval = 0;
	int ret = 0;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	if (dapm_kcontrol_is_powered(kcontrol) && reg != SND_SOC_NOPM) {
		ret = soc_dapm_read(dapm, reg, &reg_val);
		val = (reg_val >> shift) & mask;

		if (ret == 0 && reg != mc->rreg)
			ret = soc_dapm_read(dapm, mc->rreg, &reg_val);

		if (snd_soc_volsw_is_stereo(mc))
			rval = (reg_val >> mc->rshift) & mask;
	} else {
		reg_val = dapm_kcontrol_get_value(kcontrol);
		val = reg_val & mask;

		if (snd_soc_volsw_is_stereo(mc))
			rval = (reg_val >> width) & mask;
	}
	mutex_unlock(&card->dapm_mutex);

	if (ret)
		return ret;

	if (invert)
		ucontrol->value.integer.value[0] = max - val;
	else
		ucontrol->value.integer.value[0] = val;

	if (snd_soc_volsw_is_stereo(mc)) {
		if (invert)
			ucontrol->value.integer.value[1] = max - rval;
		else
			ucontrol->value.integer.value[1] = rval;
	}

	return ret;
}