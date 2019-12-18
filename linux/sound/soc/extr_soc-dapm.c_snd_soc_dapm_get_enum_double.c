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
struct soc_enum {scalar_t__ reg; unsigned int shift_l; unsigned int mask; unsigned int shift_r; } ;
struct snd_soc_dapm_context {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm_mutex; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_CLASS_RUNTIME ; 
 scalar_t__ SND_SOC_NOPM ; 
 unsigned int dapm_kcontrol_get_value (struct snd_kcontrol*) ; 
 scalar_t__ dapm_kcontrol_is_powered (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 void* snd_soc_enum_val_to_item (struct soc_enum*,unsigned int) ; 
 int soc_dapm_read (struct snd_soc_dapm_context*,scalar_t__,unsigned int*) ; 

int snd_soc_dapm_get_enum_double(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct snd_soc_card *card = dapm->card;
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int reg_val, val;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	if (e->reg != SND_SOC_NOPM && dapm_kcontrol_is_powered(kcontrol)) {
		int ret = soc_dapm_read(dapm, e->reg, &reg_val);
		if (ret) {
			mutex_unlock(&card->dapm_mutex);
			return ret;
		}
	} else {
		reg_val = dapm_kcontrol_get_value(kcontrol);
	}
	mutex_unlock(&card->dapm_mutex);

	val = (reg_val >> e->shift_l) & e->mask;
	ucontrol->value.enumerated.item[0] = snd_soc_enum_val_to_item(e, val);
	if (e->shift_l != e->shift_r) {
		val = (reg_val >> e->shift_r) & e->mask;
		val = snd_soc_enum_val_to_item(e, val);
		ucontrol->value.enumerated.item[1] = val;
	}

	return 0;
}