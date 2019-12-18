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
struct sof_ipc_pcm_params_reply {int dummy; } ;
struct TYPE_7__ {int size; int cmd; } ;
struct TYPE_5__ {int size; } ;
struct TYPE_6__ {int direction; int sample_valid_bytes; int /*<<< orphan*/  frame_fmt; int /*<<< orphan*/  host_period_bytes; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  buffer_fmt; TYPE_1__ hdr; } ;
struct sof_ipc_pcm_params {TYPE_3__ hdr; TYPE_2__ params; int /*<<< orphan*/  comp_id; } ;
struct snd_sof_widget {TYPE_4__* widget; int /*<<< orphan*/  comp_id; struct snd_sof_dev* sdev; } ;
struct snd_sof_pcm {struct snd_pcm_hw_params* params; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
struct snd_pcm_hw_params {int dummy; } ;
typedef  int /*<<< orphan*/  pcm ;
typedef  int /*<<< orphan*/  ipc_params_reply ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  sname; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16 130 
#define  SNDRV_PCM_FORMAT_S24 129 
#define  SNDRV_PCM_FORMAT_S32 128 
 int /*<<< orphan*/  SOF_IPC_BUFFER_INTERLEAVED ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_S16_LE ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_S24_4LE ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_S32_LE ; 
 int SOF_IPC_GLB_STREAM_MSG ; 
 int SOF_IPC_STREAM_PCM_PARAMS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sof_ipc_pcm_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_name (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_pcm_params*,int,struct sof_ipc_pcm_params_reply*,int) ; 

__attribute__((used)) static int ipc_pcm_params(struct snd_sof_widget *swidget, int dir)
{
	struct sof_ipc_pcm_params_reply ipc_params_reply;
	struct snd_sof_dev *sdev = swidget->sdev;
	struct sof_ipc_pcm_params pcm;
	struct snd_pcm_hw_params *params;
	struct snd_sof_pcm *spcm;
	int ret = 0;

	memset(&pcm, 0, sizeof(pcm));

	/* get runtime PCM params using widget's stream name */
	spcm = snd_sof_find_spcm_name(sdev, swidget->widget->sname);
	if (!spcm) {
		dev_err(sdev->dev, "error: cannot find PCM for %s\n",
			swidget->widget->name);
		return -EINVAL;
	}

	params = &spcm->params[dir];

	/* set IPC PCM params */
	pcm.hdr.size = sizeof(pcm);
	pcm.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_PCM_PARAMS;
	pcm.comp_id = swidget->comp_id;
	pcm.params.hdr.size = sizeof(pcm.params);
	pcm.params.direction = dir;
	pcm.params.sample_valid_bytes = params_width(params) >> 3;
	pcm.params.buffer_fmt = SOF_IPC_BUFFER_INTERLEAVED;
	pcm.params.rate = params_rate(params);
	pcm.params.channels = params_channels(params);
	pcm.params.host_period_bytes = params_period_bytes(params);

	/* set format */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S16_LE;
		break;
	case SNDRV_PCM_FORMAT_S24:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S24_4LE;
		break;
	case SNDRV_PCM_FORMAT_S32:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S32_LE;
		break;
	default:
		return -EINVAL;
	}

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, pcm.hdr.cmd, &pcm, sizeof(pcm),
				 &ipc_params_reply, sizeof(ipc_params_reply));
	if (ret < 0)
		dev_err(sdev->dev, "error: pcm params failed for %s\n",
			swidget->widget->name);

	return ret;
}