#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */
 int _snd_cmipci_uswitch_get (struct snd_kcontrol*,struct snd_ctl_elem_value*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmipci_switch_arg_spdif_enable ; 
 int /*<<< orphan*/  cmipci_switch_arg_spdo2dac ; 

__attribute__((used)) static int snd_cmipci_spdout_enable_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	int changed;
	changed = _snd_cmipci_uswitch_get(kcontrol, ucontrol, &cmipci_switch_arg_spdif_enable);
	changed |= _snd_cmipci_uswitch_get(kcontrol, ucontrol, &cmipci_switch_arg_spdo2dac);
	return changed;
}