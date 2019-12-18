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
struct sof_ipc_ctrl_data {struct sof_abi_hdr* data; } ;
struct sof_abi_hdr {int size; } ;
struct TYPE_4__ {struct snd_sof_control* private; } ;
struct soc_bytes_ext {int max; TYPE_1__ dobj; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dev; } ;
struct snd_sof_control {int /*<<< orphan*/  cmd; struct sof_ipc_ctrl_data* control_data; struct snd_sof_dev* sdev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__ bytes; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOF_CTRL_TYPE_DATA_SET ; 
 int /*<<< orphan*/  SOF_IPC_COMP_SET_DATA ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  memcpy (struct sof_abi_hdr*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_ipc_set_get_comp_data (int /*<<< orphan*/ ,struct snd_sof_control*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int snd_sof_bytes_put(struct snd_kcontrol *kcontrol,
		      struct snd_ctl_elem_value *ucontrol)
{
	struct soc_bytes_ext *be =
		(struct soc_bytes_ext *)kcontrol->private_value;
	struct snd_sof_control *scontrol = be->dobj.private;
	struct snd_sof_dev *sdev = scontrol->sdev;
	struct sof_ipc_ctrl_data *cdata = scontrol->control_data;
	struct sof_abi_hdr *data = cdata->data;
	size_t size = data->size + sizeof(*data);

	if (be->max > sizeof(ucontrol->value.bytes.data)) {
		dev_err_ratelimited(sdev->dev,
				    "error: data max %d exceeds ucontrol data array size\n",
				    be->max);
		return -EINVAL;
	}

	if (size > be->max) {
		dev_err_ratelimited(sdev->dev,
				    "error: size too big %zu bytes max is %d\n",
				    size, be->max);
		return -EINVAL;
	}

	/* copy from kcontrol */
	memcpy(data, ucontrol->value.bytes.data, size);

	/* notify DSP of byte control updates */
	if (pm_runtime_active(sdev->dev))
		snd_sof_ipc_set_get_comp_data(sdev->ipc, scontrol,
					      SOF_IPC_COMP_SET_DATA,
					      SOF_CTRL_TYPE_DATA_SET,
					      scontrol->cmd,
					      true);

	return 0;
}