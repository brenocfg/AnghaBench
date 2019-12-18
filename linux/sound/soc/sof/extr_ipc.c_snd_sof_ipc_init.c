#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_sof_ipc_msg {int ipc_complete; int /*<<< orphan*/  waitq; void* reply_data; void* msg_data; } ;
struct snd_sof_ipc {struct snd_sof_ipc_msg msg; struct snd_sof_dev* sdev; int /*<<< orphan*/  tx_mutex; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SOF_IPC_MSG_MAX_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 

struct snd_sof_ipc *snd_sof_ipc_init(struct snd_sof_dev *sdev)
{
	struct snd_sof_ipc *ipc;
	struct snd_sof_ipc_msg *msg;

	/* check if mandatory ops required for ipc are defined */
	if (!sof_ops(sdev)->fw_ready) {
		dev_err(sdev->dev, "error: ipc mandatory ops not defined\n");
		return NULL;
	}

	ipc = devm_kzalloc(sdev->dev, sizeof(*ipc), GFP_KERNEL);
	if (!ipc)
		return NULL;

	mutex_init(&ipc->tx_mutex);
	ipc->sdev = sdev;
	msg = &ipc->msg;

	/* indicate that we aren't sending a message ATM */
	msg->ipc_complete = true;

	/* pre-allocate message data */
	msg->msg_data = devm_kzalloc(sdev->dev, SOF_IPC_MSG_MAX_SIZE,
				     GFP_KERNEL);
	if (!msg->msg_data)
		return NULL;

	msg->reply_data = devm_kzalloc(sdev->dev, SOF_IPC_MSG_MAX_SIZE,
				       GFP_KERNEL);
	if (!msg->reply_data)
		return NULL;

	init_waitqueue_head(&msg->waitq);

	return ipc;
}