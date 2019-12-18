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
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct dg* model_data; } ;
struct dg {unsigned int output_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int output_select_apply (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_update_dac_routing (struct oxygen*) ; 

__attribute__((used)) static int output_select_put(struct snd_kcontrol *ctl,
			     struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	unsigned int new = value->value.enumerated.item[0];
	int changed = 0;
	int ret;

	mutex_lock(&chip->mutex);
	if (data->output_sel != new) {
		data->output_sel = new;
		ret = output_select_apply(chip);
		changed = ret >= 0 ? 1 : ret;
		oxygen_update_dac_routing(chip);
	}
	mutex_unlock(&chip->mutex);

	return changed;
}