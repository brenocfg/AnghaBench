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
struct sof_ipc_ctrl_data_params {size_t msg_bytes; size_t pl_size; size_t hdr_bytes; int num_msg; struct sof_ipc_ctrl_data* src; struct sof_ipc_ctrl_data* dst; } ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct sof_ipc_ctrl_data {size_t num_elems; int msg_index; size_t elems_remaining; TYPE_2__ rhdr; int /*<<< orphan*/  type; } ;
struct snd_sof_dev {TYPE_3__* ipc; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SOF_IPC_MSG_MAX_SIZE ; 
 int /*<<< orphan*/  kfree (struct sof_ipc_ctrl_data*) ; 
 struct sof_ipc_ctrl_data* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sof_ipc_ctrl_data*,struct sof_ipc_ctrl_data*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sof_get_ctrl_copy_params (int /*<<< orphan*/ ,struct sof_ipc_ctrl_data*,struct sof_ipc_ctrl_data*,struct sof_ipc_ctrl_data_params*) ; 
 int sof_ipc_tx_message_unlocked (TYPE_3__*,int /*<<< orphan*/ ,struct sof_ipc_ctrl_data*,scalar_t__,struct sof_ipc_ctrl_data*,scalar_t__) ; 

__attribute__((used)) static int sof_set_get_large_ctrl_data(struct snd_sof_dev *sdev,
				       struct sof_ipc_ctrl_data *cdata,
				       struct sof_ipc_ctrl_data_params *sparams,
				       bool send)
{
	struct sof_ipc_ctrl_data *partdata;
	size_t send_bytes;
	size_t offset = 0;
	size_t msg_bytes;
	size_t pl_size;
	int err;
	int i;

	/* allocate max ipc size because we have at least one */
	partdata = kzalloc(SOF_IPC_MSG_MAX_SIZE, GFP_KERNEL);
	if (!partdata)
		return -ENOMEM;

	if (send)
		err = sof_get_ctrl_copy_params(cdata->type, cdata, partdata,
					       sparams);
	else
		err = sof_get_ctrl_copy_params(cdata->type, partdata, cdata,
					       sparams);
	if (err < 0) {
		kfree(partdata);
		return err;
	}

	msg_bytes = sparams->msg_bytes;
	pl_size = sparams->pl_size;

	/* copy the header data */
	memcpy(partdata, cdata, sparams->hdr_bytes);

	/* Serialise IPC TX */
	mutex_lock(&sdev->ipc->tx_mutex);

	/* copy the payload data in a loop */
	for (i = 0; i < sparams->num_msg; i++) {
		send_bytes = min(msg_bytes, pl_size);
		partdata->num_elems = send_bytes;
		partdata->rhdr.hdr.size = sparams->hdr_bytes + send_bytes;
		partdata->msg_index = i;
		msg_bytes -= send_bytes;
		partdata->elems_remaining = msg_bytes;

		if (send)
			memcpy(sparams->dst, sparams->src + offset, send_bytes);

		err = sof_ipc_tx_message_unlocked(sdev->ipc,
						  partdata->rhdr.hdr.cmd,
						  partdata,
						  partdata->rhdr.hdr.size,
						  partdata,
						  partdata->rhdr.hdr.size);
		if (err < 0)
			break;

		if (!send)
			memcpy(sparams->dst + offset, sparams->src, send_bytes);

		offset += pl_size;
	}

	mutex_unlock(&sdev->ipc->tx_mutex);

	kfree(partdata);
	return err;
}