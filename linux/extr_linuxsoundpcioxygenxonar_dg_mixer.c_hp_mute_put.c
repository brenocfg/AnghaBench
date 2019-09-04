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
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct dg* model_data; } ;
struct dg {int* cs4245_shadow; } ;

/* Variables and functions */
 size_t CS4245_DAC_CTRL_1 ; 
 int CS4245_MUTE_DAC ; 
 int EINVAL ; 
 int cs4245_write_spi (struct oxygen*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp_mute_put(struct snd_kcontrol *ctl,
			struct snd_ctl_elem_value *val)
{
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	int ret;
	int changed;

	if (val->value.integer.value[0] > 1)
		return -EINVAL;
	mutex_lock(&chip->mutex);
	data->cs4245_shadow[CS4245_DAC_CTRL_1] &= ~CS4245_MUTE_DAC;
	data->cs4245_shadow[CS4245_DAC_CTRL_1] |=
		(~val->value.integer.value[0] << 2) & CS4245_MUTE_DAC;
	ret = cs4245_write_spi(chip, CS4245_DAC_CTRL_1);
	changed = ret >= 0 ? 1 : ret;
	mutex_unlock(&chip->mutex);
	return changed;
}