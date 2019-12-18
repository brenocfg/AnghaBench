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
struct sof_ipc_cmd_hdr {int /*<<< orphan*/  cmd; int /*<<< orphan*/  size; } ;
struct snd_sof_ipc_msg {int reply_error; int /*<<< orphan*/  reply_size; int /*<<< orphan*/  reply_data; int /*<<< orphan*/  ipc_complete; int /*<<< orphan*/  waitq; struct sof_ipc_cmd_hdr* msg_data; } ;
struct snd_sof_ipc {struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SOF_DBG_MBOX ; 
 int SOF_DBG_REGS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_log_header (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_dbg_dump (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  snd_sof_ipc_dump (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_trace_notify_for_error (struct snd_sof_dev*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tx_wait_done(struct snd_sof_ipc *ipc, struct snd_sof_ipc_msg *msg,
			void *reply_data)
{
	struct snd_sof_dev *sdev = ipc->sdev;
	struct sof_ipc_cmd_hdr *hdr = msg->msg_data;
	int ret;

	/* wait for DSP IPC completion */
	ret = wait_event_timeout(msg->waitq, msg->ipc_complete,
				 msecs_to_jiffies(sdev->ipc_timeout));

	if (ret == 0) {
		dev_err(sdev->dev, "error: ipc timed out for 0x%x size %d\n",
			hdr->cmd, hdr->size);
		snd_sof_dsp_dbg_dump(ipc->sdev, SOF_DBG_REGS | SOF_DBG_MBOX);
		snd_sof_ipc_dump(ipc->sdev);
		snd_sof_trace_notify_for_error(ipc->sdev);
		ret = -ETIMEDOUT;
	} else {
		/* copy the data returned from DSP */
		ret = msg->reply_error;
		if (msg->reply_size)
			memcpy(reply_data, msg->reply_data, msg->reply_size);
		if (ret < 0)
			dev_err(sdev->dev, "error: ipc error for 0x%x size %zu\n",
				hdr->cmd, msg->reply_size);
		else
			ipc_log_header(sdev->dev, "ipc tx succeeded", hdr->cmd);
	}

	return ret;
}