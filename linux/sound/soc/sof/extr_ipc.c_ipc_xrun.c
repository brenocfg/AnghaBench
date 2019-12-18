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
struct sof_ipc_stream_posn {int /*<<< orphan*/  xrun_size; int /*<<< orphan*/  xrun_comp_id; int /*<<< orphan*/  host_posn; } ;
struct snd_sof_pcm_stream {int /*<<< orphan*/  substream; int /*<<< orphan*/  posn; } ;
struct snd_sof_pcm {struct snd_sof_pcm_stream* stream; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  posn ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sof_ipc_stream_posn*,int) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_comp (struct snd_sof_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snd_sof_ipc_msg_data (struct snd_sof_dev*,int /*<<< orphan*/ ,struct sof_ipc_stream_posn*,int) ; 

__attribute__((used)) static void ipc_xrun(struct snd_sof_dev *sdev, u32 msg_id)
{
	struct snd_sof_pcm_stream *stream;
	struct sof_ipc_stream_posn posn;
	struct snd_sof_pcm *spcm;
	int direction;

	spcm = snd_sof_find_spcm_comp(sdev, msg_id, &direction);
	if (!spcm) {
		dev_err(sdev->dev, "error: XRUN for unknown stream, msg_id %d\n",
			msg_id);
		return;
	}

	stream = &spcm->stream[direction];
	snd_sof_ipc_msg_data(sdev, stream->substream, &posn, sizeof(posn));

	dev_dbg(sdev->dev,  "posn XRUN: host %llx comp %d size %d\n",
		posn.host_posn, posn.xrun_comp_id, posn.xrun_size);

#if defined(CONFIG_SND_SOC_SOF_DEBUG_XRUN_STOP)
	/* stop PCM on XRUN - used for pipeline debug */
	memcpy(&stream->posn, &posn, sizeof(posn));
	snd_pcm_stop_xrun(stream->substream);
#endif
}