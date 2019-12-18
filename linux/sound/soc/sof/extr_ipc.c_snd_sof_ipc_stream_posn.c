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
struct sof_ipc_stream_posn {int dummy; } ;
struct TYPE_4__ {int size; int cmd; } ;
struct sof_ipc_stream {int /*<<< orphan*/  comp_id; TYPE_2__ hdr; } ;
struct snd_sof_pcm {TYPE_1__* stream; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
typedef  int /*<<< orphan*/  stream ;
struct TYPE_3__ {int /*<<< orphan*/  comp_id; } ;

/* Variables and functions */
 int SOF_IPC_GLB_STREAM_MSG ; 
 int SOF_IPC_STREAM_POSITION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_stream*,int,struct sof_ipc_stream_posn**,int) ; 

int snd_sof_ipc_stream_posn(struct snd_sof_dev *sdev,
			    struct snd_sof_pcm *spcm, int direction,
			    struct sof_ipc_stream_posn *posn)
{
	struct sof_ipc_stream stream;
	int err;

	/* read position via slower IPC */
	stream.hdr.size = sizeof(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_POSITION;
	stream.comp_id = spcm->stream[direction].comp_id;

	/* send IPC to the DSP */
	err = sof_ipc_tx_message(sdev->ipc,
				 stream.hdr.cmd, &stream, sizeof(stream), &posn,
				 sizeof(*posn));
	if (err < 0) {
		dev_err(sdev->dev, "error: failed to get stream %d position\n",
			stream.comp_id);
		return err;
	}

	return 0;
}