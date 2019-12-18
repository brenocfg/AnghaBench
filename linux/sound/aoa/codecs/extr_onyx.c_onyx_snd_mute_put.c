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
typedef  int u8 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct onyx {int /*<<< orphan*/  mutex; scalar_t__ analog_locked; } ;

/* Variables and functions */
 int EBUSY ; 
 int ONYX_MUTE_LEFT ; 
 int ONYX_MUTE_RIGHT ; 
 int /*<<< orphan*/  ONYX_REG_DAC_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int /*<<< orphan*/ ,int*) ; 
 int onyx_write_register (struct onyx*,int /*<<< orphan*/ ,int) ; 
 struct onyx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int onyx_snd_mute_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v = 0, c = 0;
	int err = -EBUSY;

	mutex_lock(&onyx->mutex);
	if (onyx->analog_locked)
		goto out_unlock;

	onyx_read_register(onyx, ONYX_REG_DAC_CONTROL, &v);
	c = v;
	c &= ~(ONYX_MUTE_RIGHT | ONYX_MUTE_LEFT);
	if (!ucontrol->value.integer.value[0])
		c |= ONYX_MUTE_LEFT;
	if (!ucontrol->value.integer.value[1])
		c |= ONYX_MUTE_RIGHT;
	err = onyx_write_register(onyx, ONYX_REG_DAC_CONTROL, c);

 out_unlock:
	mutex_unlock(&onyx->mutex);

	return !err ? (v != c) : err;
}