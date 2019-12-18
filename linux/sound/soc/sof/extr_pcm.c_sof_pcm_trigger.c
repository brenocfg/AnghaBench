#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int /*<<< orphan*/  cmd; } ;
struct sof_ipc_stream {TYPE_4__ hdr; int /*<<< orphan*/  comp_id; } ;
struct sof_ipc_reply {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcm_id; } ;
struct snd_sof_pcm {TYPE_3__* stream; TYPE_2__ pcm; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dev; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_soc_pcm_runtime* private_data; } ;
typedef  int /*<<< orphan*/  stream ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_7__ {int /*<<< orphan*/  comp_id; } ;
struct TYPE_5__ {scalar_t__ no_pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  SOF_IPC_GLB_STREAM_MSG ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_TRIG_PAUSE ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_TRIG_RELEASE ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_TRIG_START ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_TRIG_STOP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_dai (struct snd_sof_dev*,struct snd_soc_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_sof_pcm_platform_trigger (struct snd_sof_dev*,struct snd_pcm_substream*,int) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sof_ipc_stream*,int,struct sof_ipc_reply*,int) ; 
 int sof_pcm_dsp_pcm_free (struct snd_pcm_substream*,struct snd_sof_dev*,struct snd_sof_pcm*) ; 
 int sof_pcm_prepare (struct snd_pcm_substream*) ; 

__attribute__((used)) static int sof_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_pcm *spcm;
	struct sof_ipc_stream stream;
	struct sof_ipc_reply reply;
	bool reset_hw_params = false;
	bool ipc_first = false;
	int ret;

	/* nothing to do for BE */
	if (rtd->dai_link->no_pcm)
		return 0;

	spcm = snd_sof_find_spcm_dai(sdev, rtd);
	if (!spcm)
		return -EINVAL;

	dev_dbg(sdev->dev, "pcm: trigger stream %d dir %d cmd %d\n",
		spcm->pcm.pcm_id, substream->stream, cmd);

	stream.hdr.size = sizeof(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG;
	stream.comp_id = spcm->stream[substream->stream].comp_id;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_PAUSE;
		ipc_first = true;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_RELEASE;
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
		/* set up hw_params */
		ret = sof_pcm_prepare(substream);
		if (ret < 0) {
			dev_err(sdev->dev,
				"error: failed to set up hw_params upon resume\n");
			return ret;
		}

		/* fallthrough */
	case SNDRV_PCM_TRIGGER_START:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_START;
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
		stream.hdr.cmd |= SOF_IPC_STREAM_TRIG_STOP;
		ipc_first = true;
		reset_hw_params = true;
		break;
	default:
		dev_err(sdev->dev, "error: unhandled trigger cmd %d\n", cmd);
		return -EINVAL;
	}

	/*
	 * DMA and IPC sequence is different for start and stop. Need to send
	 * STOP IPC before stop DMA
	 */
	if (!ipc_first)
		snd_sof_pcm_platform_trigger(sdev, substream, cmd);

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, stream.hdr.cmd, &stream,
				 sizeof(stream), &reply, sizeof(reply));

	/* need to STOP DMA even if STOP IPC failed */
	if (ipc_first)
		snd_sof_pcm_platform_trigger(sdev, substream, cmd);

	/* free PCM if reset_hw_params is set and the STOP IPC is successful */
	if (!ret && reset_hw_params)
		ret = sof_pcm_dsp_pcm_free(substream, sdev, spcm);

	return ret;
}