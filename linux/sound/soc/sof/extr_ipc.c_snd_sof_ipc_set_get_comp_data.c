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
typedef  int u32 ;
struct sof_ipc_fw_version {scalar_t__ abi_version; } ;
struct sof_ipc_fw_ready {struct sof_ipc_fw_version version; } ;
struct sof_ipc_ctrl_value_comp {int dummy; } ;
struct sof_ipc_ctrl_value_chan {int dummy; } ;
struct sof_ipc_ctrl_data_params {int msg_bytes; int hdr_bytes; int elems; } ;
struct TYPE_5__ {int cmd; int size; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
struct sof_ipc_ctrl_data {int num_elems; int cmd; int type; int /*<<< orphan*/  comp_id; TYPE_3__ rhdr; scalar_t__ elems_remaining; TYPE_1__* data; scalar_t__ msg_index; int /*<<< orphan*/  chanv; } ;
struct sof_abi_hdr {int dummy; } ;
struct snd_sof_ipc {struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; int /*<<< orphan*/  mmio_bar; struct sof_ipc_fw_ready fw_ready; } ;
struct snd_sof_control {int num_channels; int /*<<< orphan*/  size; int /*<<< orphan*/  comp_id; int /*<<< orphan*/  readback_offset; struct sof_ipc_ctrl_data* control_data; } ;
typedef  enum sof_ipc_ctrl_type { ____Placeholder_sof_ipc_ctrl_type } sof_ipc_ctrl_type ;
typedef  enum sof_ipc_ctrl_cmd { ____Placeholder_sof_ipc_ctrl_cmd } sof_ipc_ctrl_cmd ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOF_ABI_VER (int,int,int /*<<< orphan*/ ) ; 
#define  SOF_CTRL_TYPE_DATA_GET 133 
#define  SOF_CTRL_TYPE_DATA_SET 132 
#define  SOF_CTRL_TYPE_VALUE_CHAN_GET 131 
#define  SOF_CTRL_TYPE_VALUE_CHAN_SET 130 
#define  SOF_CTRL_TYPE_VALUE_COMP_GET 129 
#define  SOF_CTRL_TYPE_VALUE_COMP_SET 128 
 int SOF_IPC_GLB_COMP_MSG ; 
 scalar_t__ SOF_IPC_MSG_MAX_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snd_sof_dsp_block_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  snd_sof_dsp_block_write (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_ctrl_data*,scalar_t__,struct sof_ipc_ctrl_data*,scalar_t__) ; 
 int sof_set_get_large_ctrl_data (struct snd_sof_dev*,struct sof_ipc_ctrl_data*,struct sof_ipc_ctrl_data_params*,int) ; 

int snd_sof_ipc_set_get_comp_data(struct snd_sof_ipc *ipc,
				  struct snd_sof_control *scontrol,
				  u32 ipc_cmd,
				  enum sof_ipc_ctrl_type ctrl_type,
				  enum sof_ipc_ctrl_cmd ctrl_cmd,
				  bool send)
{
	struct sof_ipc_ctrl_data *cdata = scontrol->control_data;
	struct snd_sof_dev *sdev = ipc->sdev;
	struct sof_ipc_fw_ready *ready = &sdev->fw_ready;
	struct sof_ipc_fw_version *v = &ready->version;
	struct sof_ipc_ctrl_data_params sparams;
	size_t send_bytes;
	int err;

	/* read or write firmware volume */
	if (scontrol->readback_offset != 0) {
		/* write/read value header via mmaped region */
		send_bytes = sizeof(struct sof_ipc_ctrl_value_chan) *
		cdata->num_elems;
		if (send)
			snd_sof_dsp_block_write(sdev, sdev->mmio_bar,
						scontrol->readback_offset,
						cdata->chanv, send_bytes);

		else
			snd_sof_dsp_block_read(sdev, sdev->mmio_bar,
					       scontrol->readback_offset,
					       cdata->chanv, send_bytes);
		return 0;
	}

	cdata->rhdr.hdr.cmd = SOF_IPC_GLB_COMP_MSG | ipc_cmd;
	cdata->cmd = ctrl_cmd;
	cdata->type = ctrl_type;
	cdata->comp_id = scontrol->comp_id;
	cdata->msg_index = 0;

	/* calculate header and data size */
	switch (cdata->type) {
	case SOF_CTRL_TYPE_VALUE_CHAN_GET:
	case SOF_CTRL_TYPE_VALUE_CHAN_SET:
		sparams.msg_bytes = scontrol->num_channels *
			sizeof(struct sof_ipc_ctrl_value_chan);
		sparams.hdr_bytes = sizeof(struct sof_ipc_ctrl_data);
		sparams.elems = scontrol->num_channels;
		break;
	case SOF_CTRL_TYPE_VALUE_COMP_GET:
	case SOF_CTRL_TYPE_VALUE_COMP_SET:
		sparams.msg_bytes = scontrol->num_channels *
			sizeof(struct sof_ipc_ctrl_value_comp);
		sparams.hdr_bytes = sizeof(struct sof_ipc_ctrl_data);
		sparams.elems = scontrol->num_channels;
		break;
	case SOF_CTRL_TYPE_DATA_GET:
	case SOF_CTRL_TYPE_DATA_SET:
		sparams.msg_bytes = cdata->data->size;
		sparams.hdr_bytes = sizeof(struct sof_ipc_ctrl_data) +
			sizeof(struct sof_abi_hdr);
		sparams.elems = cdata->data->size;
		break;
	default:
		return -EINVAL;
	}

	cdata->rhdr.hdr.size = sparams.msg_bytes + sparams.hdr_bytes;
	cdata->num_elems = sparams.elems;
	cdata->elems_remaining = 0;

	/* send normal size ipc in one part */
	if (cdata->rhdr.hdr.size <= SOF_IPC_MSG_MAX_SIZE) {
		err = sof_ipc_tx_message(sdev->ipc, cdata->rhdr.hdr.cmd, cdata,
					 cdata->rhdr.hdr.size, cdata,
					 cdata->rhdr.hdr.size);

		if (err < 0)
			dev_err(sdev->dev, "error: set/get ctrl ipc comp %d\n",
				cdata->comp_id);

		return err;
	}

	/* data is bigger than max ipc size, chop into smaller pieces */
	dev_dbg(sdev->dev, "large ipc size %u, control size %u\n",
		cdata->rhdr.hdr.size, scontrol->size);

	/* large messages is only supported from ABI 3.3.0 onwards */
	if (v->abi_version < SOF_ABI_VER(3, 3, 0)) {
		dev_err(sdev->dev, "error: incompatible FW ABI version\n");
		return -EINVAL;
	}

	err = sof_set_get_large_ctrl_data(sdev, cdata, &sparams, send);

	if (err < 0)
		dev_err(sdev->dev, "error: set/get large ctrl ipc comp %d\n",
			cdata->comp_id);

	return err;
}