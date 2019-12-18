#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sof_ipc_ctrl_data {TYPE_4__* chanv; } ;
struct TYPE_5__ {struct snd_sof_control* private; } ;
struct soc_mixer_control {TYPE_1__ dobj; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dev; } ;
struct snd_sof_control {unsigned int num_channels; struct sof_ipc_ctrl_data* control_data; struct snd_sof_dev* sdev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_6__ {scalar_t__* value; } ;
struct TYPE_7__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_8__ {scalar_t__ value; unsigned int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOF_CTRL_CMD_SWITCH ; 
 int /*<<< orphan*/  SOF_CTRL_TYPE_VALUE_CHAN_GET ; 
 int /*<<< orphan*/  SOF_IPC_COMP_SET_VALUE ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_ipc_set_get_comp_data (int /*<<< orphan*/ ,struct snd_sof_control*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int snd_sof_switch_put(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *sm =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_sof_control *scontrol = sm->dobj.private;
	struct snd_sof_dev *sdev = scontrol->sdev;
	struct sof_ipc_ctrl_data *cdata = scontrol->control_data;
	unsigned int i, channels = scontrol->num_channels;
	bool change = false;
	u32 value;

	/* update each channel */
	for (i = 0; i < channels; i++) {
		value = ucontrol->value.integer.value[i];
		change = change || (value != cdata->chanv[i].value);
		cdata->chanv[i].channel = i;
		cdata->chanv[i].value = value;
	}

	/* notify DSP of mixer updates */
	if (pm_runtime_active(sdev->dev))
		snd_sof_ipc_set_get_comp_data(sdev->ipc, scontrol,
					      SOF_IPC_COMP_SET_VALUE,
					      SOF_CTRL_TYPE_VALUE_CHAN_GET,
					      SOF_CTRL_CMD_SWITCH,
					      true);

	return change;
}