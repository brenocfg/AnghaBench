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
struct snd_wm8776 {int /*<<< orphan*/ ** volumes; } ;
struct snd_maya44 {int /*<<< orphan*/  mutex; struct snd_wm8776* wm; } ;
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t snd_ctl_get_ioff (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_maya44* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int maya_vol_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	struct snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	unsigned int idx = kcontrol->private_value;

	mutex_lock(&chip->mutex);
	ucontrol->value.integer.value[0] = wm->volumes[idx][0];
	ucontrol->value.integer.value[1] = wm->volumes[idx][1];
	mutex_unlock(&chip->mutex);
	return 0;
}