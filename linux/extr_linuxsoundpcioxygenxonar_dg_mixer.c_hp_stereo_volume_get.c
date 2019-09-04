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
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct dg* model_data; } ;
struct dg {int* cs4245_shadow; } ;

/* Variables and functions */
 size_t CS4245_DAC_A_CTRL ; 
 size_t CS4245_DAC_B_CTRL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp_stereo_volume_get(struct snd_kcontrol *ctl,
				struct snd_ctl_elem_value *val)
{
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	unsigned int tmp;

	mutex_lock(&chip->mutex);
	tmp = (~data->cs4245_shadow[CS4245_DAC_A_CTRL]) & 255;
	val->value.integer.value[0] = tmp;
	tmp = (~data->cs4245_shadow[CS4245_DAC_B_CTRL]) & 255;
	val->value.integer.value[1] = tmp;
	mutex_unlock(&chip->mutex);
	return 0;
}