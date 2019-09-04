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
struct soc_mixer_control {scalar_t__ min; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  max; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_info_volsw (struct snd_kcontrol*,struct snd_ctl_elem_info*) ; 

int snd_soc_info_volsw_sx(struct snd_kcontrol *kcontrol,
			  struct snd_ctl_elem_info *uinfo)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;

	snd_soc_info_volsw(kcontrol, uinfo);
	/* Max represents the number of levels in an SX control not the
	 * maximum value, so add the minimum value back on
	 */
	uinfo->value.integer.max += mc->min;

	return 0;
}