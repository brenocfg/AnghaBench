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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct cmipci {scalar_t__ spdif_playback_enabled; scalar_t__ spdif_playback_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_PLAYBACK_SPDF ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL1 ; 
 int _snd_cmipci_uswitch_put (struct snd_kcontrol*,struct snd_ctl_elem_value*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmipci_switch_arg_spdif_enable ; 
 int /*<<< orphan*/  cmipci_switch_arg_spdo2dac ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cmipci* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_cmipci_spdout_enable_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct cmipci *chip = snd_kcontrol_chip(kcontrol);
	int changed;
	changed = _snd_cmipci_uswitch_put(kcontrol, ucontrol, &cmipci_switch_arg_spdif_enable);
	changed |= _snd_cmipci_uswitch_put(kcontrol, ucontrol, &cmipci_switch_arg_spdo2dac);
	if (changed) {
		if (ucontrol->value.integer.value[0]) {
			if (chip->spdif_playback_avail)
				snd_cmipci_set_bit(chip, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		} else {
			if (chip->spdif_playback_avail)
				snd_cmipci_clear_bit(chip, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		}
	}
	chip->spdif_playback_enabled = ucontrol->value.integer.value[0];
	return changed;
}