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
struct snd_kcontrol {unsigned int private_value; struct oxygen* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct dg* model_data; } ;
struct dg {int /*<<< orphan*/ ** input_vol; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int input_vol_get(struct snd_kcontrol *ctl,
			 struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	unsigned int idx = ctl->private_value;

	mutex_lock(&chip->mutex);
	value->value.integer.value[0] = data->input_vol[idx][0];
	value->value.integer.value[1] = data->input_vol[idx][1];
	mutex_unlock(&chip->mutex);
	return 0;
}