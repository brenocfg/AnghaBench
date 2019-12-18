#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_sof_ipc_msg {size_t msg_size; size_t reply_size; int ipc_complete; int /*<<< orphan*/  header; int /*<<< orphan*/  msg_data; scalar_t__ reply_error; } ;
struct snd_sof_ipc {struct snd_sof_ipc_msg msg; scalar_t__ disable_ipc_tx; struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc_lock; struct snd_sof_ipc_msg* msg; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipc_log_header (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int snd_sof_dsp_send_msg (struct snd_sof_dev*,struct snd_sof_ipc_msg*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int tx_wait_done (struct snd_sof_ipc*,struct snd_sof_ipc_msg*,void*) ; 

__attribute__((used)) static int sof_ipc_tx_message_unlocked(struct snd_sof_ipc *ipc, u32 header,
				       void *msg_data, size_t msg_bytes,
				       void *reply_data, size_t reply_bytes)
{
	struct snd_sof_dev *sdev = ipc->sdev;
	struct snd_sof_ipc_msg *msg;
	int ret;

	if (ipc->disable_ipc_tx)
		return -ENODEV;

	/*
	 * The spin-lock is also still needed to protect message objects against
	 * other atomic contexts.
	 */
	spin_lock_irq(&sdev->ipc_lock);

	/* initialise the message */
	msg = &ipc->msg;

	msg->header = header;
	msg->msg_size = msg_bytes;
	msg->reply_size = reply_bytes;
	msg->reply_error = 0;

	/* attach any data */
	if (msg_bytes)
		memcpy(msg->msg_data, msg_data, msg_bytes);

	sdev->msg = msg;

	ret = snd_sof_dsp_send_msg(sdev, msg);
	/* Next reply that we receive will be related to this message */
	if (!ret)
		msg->ipc_complete = false;

	spin_unlock_irq(&sdev->ipc_lock);

	if (ret < 0) {
		/* So far IPC TX never fails, consider making the above void */
		dev_err_ratelimited(sdev->dev,
				    "error: ipc tx failed with error %d\n",
				    ret);
		return ret;
	}

	ipc_log_header(sdev->dev, "ipc tx", msg->header);

	/* now wait for completion */
	if (!ret)
		ret = tx_wait_done(ipc, msg, reply_data);

	return ret;
}