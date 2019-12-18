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
typedef  int u32 ;
struct sof_ipc_cmd_hdr {int cmd; } ;
struct snd_sof_dev {int boot_complete; int /*<<< orphan*/  dev; int /*<<< orphan*/  boot_wait; } ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_2__ {int (* fw_ready ) (struct snd_sof_dev*,int) ;} ;

/* Variables and functions */
 int SOF_CMD_TYPE_MASK ; 
 int SOF_GLB_TYPE_MASK ; 
#define  SOF_IPC_FW_READY 135 
#define  SOF_IPC_GLB_COMPOUND 134 
#define  SOF_IPC_GLB_COMP_MSG 133 
#define  SOF_IPC_GLB_PM_MSG 132 
#define  SOF_IPC_GLB_REPLY 131 
#define  SOF_IPC_GLB_STREAM_MSG 130 
#define  SOF_IPC_GLB_TPLG_MSG 129 
#define  SOF_IPC_GLB_TRACE_MSG 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ipc_log_header (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipc_stream_message (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  ipc_trace_message (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  snd_sof_ipc_msg_data (struct snd_sof_dev*,int /*<<< orphan*/ *,struct sof_ipc_cmd_hdr*,int) ; 
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 int stub1 (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_sof_ipc_msgs_rx(struct snd_sof_dev *sdev)
{
	struct sof_ipc_cmd_hdr hdr;
	u32 cmd, type;
	int err = 0;

	/* read back header */
	snd_sof_ipc_msg_data(sdev, NULL, &hdr, sizeof(hdr));
	ipc_log_header(sdev->dev, "ipc rx", hdr.cmd);

	cmd = hdr.cmd & SOF_GLB_TYPE_MASK;
	type = hdr.cmd & SOF_CMD_TYPE_MASK;

	/* check message type */
	switch (cmd) {
	case SOF_IPC_GLB_REPLY:
		dev_err(sdev->dev, "error: ipc reply unknown\n");
		break;
	case SOF_IPC_FW_READY:
		/* check for FW boot completion */
		if (!sdev->boot_complete) {
			err = sof_ops(sdev)->fw_ready(sdev, cmd);
			if (err < 0) {
				/*
				 * this indicates a mismatch in ABI
				 * between the driver and fw
				 */
				dev_err(sdev->dev, "error: ABI mismatch %d\n",
					err);
			} else {
				/* firmware boot completed OK */
				sdev->boot_complete = true;
			}

			/* wake up firmware loader */
			wake_up(&sdev->boot_wait);
		}
		break;
	case SOF_IPC_GLB_COMPOUND:
	case SOF_IPC_GLB_TPLG_MSG:
	case SOF_IPC_GLB_PM_MSG:
	case SOF_IPC_GLB_COMP_MSG:
		break;
	case SOF_IPC_GLB_STREAM_MSG:
		/* need to pass msg id into the function */
		ipc_stream_message(sdev, hdr.cmd);
		break;
	case SOF_IPC_GLB_TRACE_MSG:
		ipc_trace_message(sdev, type);
		break;
	default:
		dev_err(sdev->dev, "error: unknown DSP message 0x%x\n", cmd);
		break;
	}

	ipc_log_header(sdev->dev, "ipc rx done", hdr.cmd);
}