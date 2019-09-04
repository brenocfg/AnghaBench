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
struct snd_wm8776 {unsigned int switch_bits; } ;
struct snd_maya44 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ice; struct snd_wm8776* wm; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 unsigned int GET_SW_VAL_IDX (int /*<<< orphan*/ ) ; 
 unsigned int GET_SW_VAL_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SW_VAL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t snd_ctl_get_ioff (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_maya44* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int wm8776_write_bits (int /*<<< orphan*/ ,struct snd_wm8776*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int maya_sw_put(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	struct snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	unsigned int idx = GET_SW_VAL_IDX(kcontrol->private_value);
	unsigned int mask, val;
	int changed;

	mutex_lock(&chip->mutex);
	mask = 1 << idx;
	wm->switch_bits &= ~mask;
	val = ucontrol->value.integer.value[0];
	if (val)
		wm->switch_bits |= mask;
	mask = GET_SW_VAL_MASK(kcontrol->private_value);
	changed = wm8776_write_bits(chip->ice, wm,
				    GET_SW_VAL_REG(kcontrol->private_value),
				    mask, val ? mask : 0);
	mutex_unlock(&chip->mutex);
	return changed;
}