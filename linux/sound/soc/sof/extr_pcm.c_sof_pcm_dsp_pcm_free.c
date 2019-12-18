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
struct snd_sof_pcm {int* prepared; TYPE_1__* stream; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; } ;
struct snd_pcm_substream {size_t stream; } ;
typedef  int /*<<< orphan*/  stream ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_3__ {int /*<<< orphan*/  comp_id; } ;

/* Variables and functions */
 int SOF_IPC_GLB_STREAM_MSG ; 
 int SOF_IPC_STREAM_PCM_FREE ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_stream*,int,struct sof_ipc_reply*,int) ; 

__attribute__((used)) static int sof_pcm_dsp_pcm_free(struct snd_pcm_substream *substream,
				struct snd_sof_dev *sdev,
				struct snd_sof_pcm *spcm)
{
	struct sof_ipc_stream stream;
	struct sof_ipc_reply reply;
	int ret;

	stream.hdr.size = sizeof(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_PCM_FREE;
	stream.comp_id = spcm->stream[substream->stream].comp_id;

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, stream.hdr.cmd, &stream,
				 sizeof(stream), &reply, sizeof(reply));
	if (!ret)
		spcm->prepared[substream->stream] = false;

	return ret;
}