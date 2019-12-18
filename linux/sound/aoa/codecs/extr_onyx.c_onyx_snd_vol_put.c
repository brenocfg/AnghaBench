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
struct onyx {int /*<<< orphan*/  mutex; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ONYX_REG_DAC_ATTEN_LEFT ; 
 int /*<<< orphan*/  ONYX_REG_DAC_ATTEN_RIGHT ; 
 scalar_t__ VOLUME_RANGE_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  onyx_write_register (struct onyx*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct onyx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int onyx_snd_vol_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct onyx *onyx = snd_kcontrol_chip(kcontrol);
	s8 l, r;

	if (ucontrol->value.integer.value[0] < -128 + VOLUME_RANGE_SHIFT ||
	    ucontrol->value.integer.value[0] > -1 + VOLUME_RANGE_SHIFT)
		return -EINVAL;
	if (ucontrol->value.integer.value[1] < -128 + VOLUME_RANGE_SHIFT ||
	    ucontrol->value.integer.value[1] > -1 + VOLUME_RANGE_SHIFT)
		return -EINVAL;

	mutex_lock(&onyx->mutex);
	onyx_read_register(onyx, ONYX_REG_DAC_ATTEN_LEFT, &l);
	onyx_read_register(onyx, ONYX_REG_DAC_ATTEN_RIGHT, &r);

	if (l + VOLUME_RANGE_SHIFT == ucontrol->value.integer.value[0] &&
	    r + VOLUME_RANGE_SHIFT == ucontrol->value.integer.value[1]) {
		mutex_unlock(&onyx->mutex);
		return 0;
	}

	onyx_write_register(onyx, ONYX_REG_DAC_ATTEN_LEFT,
			    ucontrol->value.integer.value[0]
			     - VOLUME_RANGE_SHIFT);
	onyx_write_register(onyx, ONYX_REG_DAC_ATTEN_RIGHT,
			    ucontrol->value.integer.value[1]
			     - VOLUME_RANGE_SHIFT);
	mutex_unlock(&onyx->mutex);

	return 1;
}