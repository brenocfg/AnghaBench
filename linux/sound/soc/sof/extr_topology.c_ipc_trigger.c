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
struct TYPE_4__ {int size; int cmd; } ;
struct sof_ipc_stream {TYPE_2__ hdr; int /*<<< orphan*/  comp_id; } ;
struct sof_ipc_reply {int dummy; } ;
struct snd_sof_widget {TYPE_1__* widget; int /*<<< orphan*/  comp_id; struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
typedef  int /*<<< orphan*/  stream ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SOF_IPC_GLB_STREAM_MSG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_stream*,int,struct sof_ipc_reply*,int) ; 

__attribute__((used)) static int ipc_trigger(struct snd_sof_widget *swidget, int cmd)
{
	struct snd_sof_dev *sdev = swidget->sdev;
	struct sof_ipc_stream stream;
	struct sof_ipc_reply reply;
	int ret = 0;

	/* set IPC stream params */
	stream.hdr.size = sizeof(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | cmd;
	stream.comp_id = swidget->comp_id;

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, stream.hdr.cmd, &stream,
				 sizeof(stream), &reply, sizeof(reply));
	if (ret < 0)
		dev_err(sdev->dev, "error: failed to trigger %s\n",
			swidget->widget->name);

	return ret;
}