#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sst_gain_value {int l_gain; int r_gain; int mute; int ramp_duration; } ;
struct sst_gain_mixer_control {int type; int pipe_id; int instance_id; int /*<<< orphan*/  module_id; int /*<<< orphan*/  task_id; TYPE_3__* w; int /*<<< orphan*/  pname; struct sst_gain_value* gain_val; } ;
struct sst_data {int /*<<< orphan*/  lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {scalar_t__ power; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SST_GAIN_MUTE 130 
#define  SST_GAIN_RAMP_DURATION 129 
#define  SST_GAIN_TLV 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int sst_send_gain_cmd (struct sst_data*,struct sst_gain_value*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_gain_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	int ret = 0;
	struct snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	struct sst_data *drv = snd_soc_component_get_drvdata(cmpnt);
	struct sst_gain_mixer_control *mc = (void *)kcontrol->private_value;
	struct sst_gain_value *gv = mc->gain_val;

	mutex_lock(&drv->lock);

	switch (mc->type) {
	case SST_GAIN_TLV:
		gv->l_gain = ucontrol->value.integer.value[0];
		gv->r_gain = ucontrol->value.integer.value[1];
		dev_dbg(cmpnt->dev, "%s: Volume %d, %d\n",
				mc->pname, gv->l_gain, gv->r_gain);
		break;

	case SST_GAIN_MUTE:
		gv->mute = !ucontrol->value.integer.value[0];
		dev_dbg(cmpnt->dev, "%s: Mute %d\n", mc->pname, gv->mute);
		break;

	case SST_GAIN_RAMP_DURATION:
		gv->ramp_duration = ucontrol->value.integer.value[0];
		dev_dbg(cmpnt->dev, "%s: Ramp Delay%d\n",
					mc->pname, gv->ramp_duration);
		break;

	default:
		mutex_unlock(&drv->lock);
		dev_err(cmpnt->dev, "Invalid Input- gain type:%d\n",
				mc->type);
		return -EINVAL;
	}

	if (mc->w && mc->w->power)
		ret = sst_send_gain_cmd(drv, gv, mc->task_id,
			mc->pipe_id | mc->instance_id, mc->module_id, 0);
	mutex_unlock(&drv->lock);

	return ret;
}