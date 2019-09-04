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
typedef  scalar_t__ u8 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct onyx {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INPUTGAIN_RANGE_SHIFT ; 
 scalar_t__ ONYX_ADC_PGA_GAIN_MASK ; 
 int /*<<< orphan*/  ONYX_REG_ADC_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  onyx_write_register (struct onyx*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct onyx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int onyx_snd_inputgain_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v, n;

	if (ucontrol->value.integer.value[0] < 3 + INPUTGAIN_RANGE_SHIFT ||
	    ucontrol->value.integer.value[0] > 28 + INPUTGAIN_RANGE_SHIFT)
		return -EINVAL;
	mutex_lock(&onyx->mutex);
	onyx_read_register(onyx, ONYX_REG_ADC_CONTROL, &v);
	n = v;
	n &= ~ONYX_ADC_PGA_GAIN_MASK;
	n |= (ucontrol->value.integer.value[0] - INPUTGAIN_RANGE_SHIFT)
		& ONYX_ADC_PGA_GAIN_MASK;
	onyx_write_register(onyx, ONYX_REG_ADC_CONTROL, n);
	mutex_unlock(&onyx->mutex);

	return n != v;
}