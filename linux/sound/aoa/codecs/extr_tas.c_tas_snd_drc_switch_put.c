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
struct tas {int drc_enabled; int /*<<< orphan*/  mtx; scalar_t__ hw_enabled; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tas* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  tas3004_set_drc (struct tas*) ; 

__attribute__((used)) static int tas_snd_drc_switch_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	if (tas->drc_enabled == ucontrol->value.integer.value[0]) {
		mutex_unlock(&tas->mtx);
		return 0;
	}

	tas->drc_enabled = !!ucontrol->value.integer.value[0];
	if (tas->hw_enabled)
		tas3004_set_drc(tas);
	mutex_unlock(&tas->mtx);
	return 1;
}