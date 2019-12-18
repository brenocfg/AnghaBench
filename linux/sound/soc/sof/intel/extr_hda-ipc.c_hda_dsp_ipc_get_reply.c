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
struct TYPE_3__ {int size; int /*<<< orphan*/  cmd; } ;
struct sof_ipc_reply {int error; TYPE_1__ hdr; } ;
struct sof_ipc_cmd_hdr {int cmd; } ;
struct snd_sof_ipc_msg {int reply_size; int reply_error; struct sof_ipc_reply* reply_data; struct sof_ipc_cmd_hdr* msg_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct snd_sof_dev {TYPE_2__ host_box; int /*<<< orphan*/  dev; struct snd_sof_ipc_msg* msg; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int EINVAL ; 
 int SOF_IPC_GLB_PM_MSG ; 
 int /*<<< orphan*/  SOF_IPC_GLB_REPLY ; 
 int SOF_IPC_PM_CTX_SAVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (struct sof_ipc_reply*,struct sof_ipc_reply*,int) ; 
 int /*<<< orphan*/  sof_mailbox_read (struct snd_sof_dev*,int /*<<< orphan*/ ,struct sof_ipc_reply*,int) ; 

void hda_dsp_ipc_get_reply(struct snd_sof_dev *sdev)
{
	struct snd_sof_ipc_msg *msg = sdev->msg;
	struct sof_ipc_reply reply;
	struct sof_ipc_cmd_hdr *hdr;
	int ret = 0;

	/*
	 * Sometimes, there is unexpected reply ipc arriving. The reply
	 * ipc belongs to none of the ipcs sent from driver.
	 * In this case, the driver must ignore the ipc.
	 */
	if (!msg) {
		dev_warn(sdev->dev, "unexpected ipc interrupt raised!\n");
		return;
	}

	hdr = msg->msg_data;
	if (hdr->cmd == (SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_CTX_SAVE)) {
		/*
		 * memory windows are powered off before sending IPC reply,
		 * so we can't read the mailbox for CTX_SAVE reply.
		 */
		reply.error = 0;
		reply.hdr.cmd = SOF_IPC_GLB_REPLY;
		reply.hdr.size = sizeof(reply);
		memcpy(msg->reply_data, &reply, sizeof(reply));
		goto out;
	}

	/* get IPC reply from DSP in the mailbox */
	sof_mailbox_read(sdev, sdev->host_box.offset, &reply,
			 sizeof(reply));

	if (reply.error < 0) {
		memcpy(msg->reply_data, &reply, sizeof(reply));
		ret = reply.error;
	} else {
		/* reply correct size ? */
		if (reply.hdr.size != msg->reply_size) {
			dev_err(sdev->dev, "error: reply expected %zu got %u bytes\n",
				msg->reply_size, reply.hdr.size);
			ret = -EINVAL;
		}

		/* read the message */
		if (msg->reply_size > 0)
			sof_mailbox_read(sdev, sdev->host_box.offset,
					 msg->reply_data, msg->reply_size);
	}

out:
	msg->reply_error = ret;

}