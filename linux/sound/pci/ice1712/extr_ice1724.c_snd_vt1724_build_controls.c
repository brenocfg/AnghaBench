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
struct snd_kcontrol_new {int count; } ;
struct snd_ice1712 {scalar_t__ num_total_dacs; int /*<<< orphan*/  card; scalar_t__ vt1720; int /*<<< orphan*/  own_routing; } ;

/* Variables and functions */
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ice1712*) ; 
 struct snd_kcontrol_new snd_vt1724_eeprom ; 
 struct snd_kcontrol_new snd_vt1724_mixer_pro_analog_route ; 
 struct snd_kcontrol_new snd_vt1724_mixer_pro_peak ; 
 struct snd_kcontrol_new snd_vt1724_pro_internal_clock ; 
 struct snd_kcontrol_new snd_vt1724_pro_rate_locking ; 
 struct snd_kcontrol_new snd_vt1724_pro_rate_reset ; 

__attribute__((used)) static int snd_vt1724_build_controls(struct snd_ice1712 *ice)
{
	int err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_eeprom, ice));
	if (err < 0)
		return err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_pro_internal_clock, ice));
	if (err < 0)
		return err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_pro_rate_locking, ice));
	if (err < 0)
		return err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_pro_rate_reset, ice));
	if (err < 0)
		return err;

	if (!ice->own_routing && ice->num_total_dacs > 0) {
		struct snd_kcontrol_new tmp = snd_vt1724_mixer_pro_analog_route;
		tmp.count = ice->num_total_dacs;
		if (ice->vt1720 && tmp.count > 2)
			tmp.count = 2;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&tmp, ice));
		if (err < 0)
			return err;
	}

	return snd_ctl_add(ice->card,
			   snd_ctl_new1(&snd_vt1724_mixer_pro_peak, ice));
}