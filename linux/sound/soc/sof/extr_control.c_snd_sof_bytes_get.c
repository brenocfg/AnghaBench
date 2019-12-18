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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_sof_control {struct sof_ipc_ctrl_data* control_data; struct snd_sof_dev* sdev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__ bytes; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct sof_abi_hdr*,size_t) ; 

int snd_sof_bytes_get(struct snd_kcontrol *kcontrol,
		      struct snd_ctl_elem_value *ucontrol)
{
	struct soc_bytes_ext *be =
		(struct soc_bytes_ext *)kcontrol->private_value;
	struct snd_sof_control *scontrol = be->dobj.private;
	struct snd_sof_dev *sdev = scontrol->sdev;
	struct sof_ipc_ctrl_data *cdata = scontrol->control_data;
	struct sof_abi_hdr *data = cdata->data;
	size_t size;
	int ret = 0;

	if (be->max > sizeof(ucontrol->value.bytes.data)) {
		dev_err_ratelimited(sdev->dev,
				    "error: data max %d exceeds ucontrol data array size\n",
				    be->max);
		return -EINVAL;
	}

	size = data->size + sizeof(*data);
	if (size > be->max) {
		dev_err_ratelimited(sdev->dev,
				    "error: DSP sent %zu bytes max is %d\n",
				    size, be->max);
		ret = -EINVAL;
		goto out;
	}

	/* copy back to kcontrol */
	memcpy(ucontrol->value.bytes.data, data, size);

out:
	return ret;
}