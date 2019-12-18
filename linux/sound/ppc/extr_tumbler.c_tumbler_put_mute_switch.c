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
struct snd_pmac {struct pmac_tumbler* mixer_data; scalar_t__ auto_mute; scalar_t__ update_automute; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct pmac_gpio {int dummy; } ;
struct pmac_tumbler {struct pmac_gpio line_mute; struct pmac_gpio amp_mute; struct pmac_gpio hp_mute; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  TUMBLER_MUTE_AMP 130 
#define  TUMBLER_MUTE_HP 129 
#define  TUMBLER_MUTE_LINE 128 
 int /*<<< orphan*/  check_audio_gpio (struct pmac_gpio*) ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  write_audio_gpio (struct pmac_gpio*,int) ; 

__attribute__((used)) static int tumbler_put_mute_switch(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	struct pmac_tumbler *mix;
	struct pmac_gpio *gp;
	int val;
#ifdef PMAC_SUPPORT_AUTOMUTE
	if (chip->update_automute && chip->auto_mute)
		return 0; /* don't touch in the auto-mute mode */
#endif	
	if (! (mix = chip->mixer_data))
		return -ENODEV;
	switch(kcontrol->private_value) {
	case TUMBLER_MUTE_HP:
		gp = &mix->hp_mute;	break;
	case TUMBLER_MUTE_AMP:
		gp = &mix->amp_mute;	break;
	case TUMBLER_MUTE_LINE:
		gp = &mix->line_mute;	break;
	default:
		gp = NULL;
	}
	if (gp == NULL)
		return -EINVAL;
	val = ! check_audio_gpio(gp);
	if (val != ucontrol->value.integer.value[0]) {
		write_audio_gpio(gp, ! ucontrol->value.integer.value[0]);
		return 1;
	}
	return 0;
}