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
struct tda7419_vol_control {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_1__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 scalar_t__ tda7419_vol_is_stereo (struct tda7419_vol_control*) ; 

__attribute__((used)) static int tda7419_vol_info(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_info *uinfo)
{
	struct tda7419_vol_control *tvc =
		(struct tda7419_vol_control *)kcontrol->private_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = tda7419_vol_is_stereo(tvc) ? 2 : 1;
	uinfo->value.integer.min = tvc->min;
	uinfo->value.integer.max = tvc->max;

	return 0;
}