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
 int /*<<< orphan*/  NID_PATH_VOL_CTL ; 
 int cap_put_caller (struct snd_kcontrol*,struct snd_ctl_elem_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_mixer_amp_volume_put ; 

__attribute__((used)) static int cap_vol_put(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_value *ucontrol)
{
	return cap_put_caller(kcontrol, ucontrol,
			      snd_hda_mixer_amp_volume_put,
			      NID_PATH_VOL_CTL);
}