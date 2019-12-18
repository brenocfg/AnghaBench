#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sof_ipc_pcm_params_reply {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  size; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  pages; } ;
struct TYPE_11__ {int size; } ;
struct TYPE_16__ {size_t direction; int sample_valid_bytes; int sample_container_bytes; int /*<<< orphan*/  stream_tag; int /*<<< orphan*/  frame_fmt; int /*<<< orphan*/  host_period_bytes; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  buffer_fmt; TYPE_6__ buffer; TYPE_3__ hdr; } ;
struct TYPE_15__ {int size; int cmd; } ;
struct sof_ipc_pcm_params {TYPE_8__ params; TYPE_7__ hdr; int /*<<< orphan*/  comp_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  pcm_id; } ;
struct snd_sof_pcm {int* prepared; int /*<<< orphan*/ * params; TYPE_5__* stream; TYPE_2__ pcm; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_area; } ;
struct snd_pcm_hw_params {int dummy; } ;
typedef  int /*<<< orphan*/  pcm ;
typedef  int /*<<< orphan*/  ipc_params_reply ;
struct TYPE_12__ {int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {TYPE_4__ page_table; int /*<<< orphan*/  comp_id; } ;
struct TYPE_9__ {scalar_t__ no_pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  PFN_UP (int /*<<< orphan*/ ) ; 
#define  SNDRV_PCM_FORMAT_FLOAT 131 
#define  SNDRV_PCM_FORMAT_S16 130 
#define  SNDRV_PCM_FORMAT_S24 129 
#define  SNDRV_PCM_FORMAT_S32 128 
 int /*<<< orphan*/  SOF_IPC_BUFFER_INTERLEAVED ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_FLOAT ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_S16_LE ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_S24_4LE ; 
 int /*<<< orphan*/  SOF_IPC_FRAME_S32_LE ; 
 int SOF_IPC_GLB_STREAM_MSG ; 
 int SOF_IPC_STREAM_PCM_PARAMS ; 
 int create_page_table (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct snd_pcm_hw_params*,int) ; 
 int /*<<< orphan*/  memset (struct sof_ipc_pcm_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_physical_width (int) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_dai (struct snd_sof_dev*,struct snd_soc_pcm_runtime*) ; 
 int snd_sof_pcm_platform_hw_params (struct snd_sof_dev*,struct snd_pcm_substream*,struct snd_pcm_hw_params*,TYPE_8__*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_pcm_params*,int,struct sof_ipc_pcm_params_reply*,int) ; 
 int sof_pcm_dsp_params (struct snd_sof_pcm*,struct snd_pcm_substream*,struct sof_ipc_pcm_params_reply*) ; 

__attribute__((used)) static int sof_pcm_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_pcm *spcm;
	struct sof_ipc_pcm_params pcm;
	struct sof_ipc_pcm_params_reply ipc_params_reply;
	int ret;

	/* nothing to do for BE */
	if (rtd->dai_link->no_pcm)
		return 0;

	spcm = snd_sof_find_spcm_dai(sdev, rtd);
	if (!spcm)
		return -EINVAL;

	dev_dbg(sdev->dev, "pcm: hw params stream %d dir %d\n",
		spcm->pcm.pcm_id, substream->stream);

	memset(&pcm, 0, sizeof(pcm));

	/* allocate audio buffer pages */
	ret = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(params));
	if (ret < 0) {
		dev_err(sdev->dev, "error: could not allocate %d bytes for PCM %d\n",
			params_buffer_bytes(params), spcm->pcm.pcm_id);
		return ret;
	}
	if (ret) {
		/*
		 * ret == 1 means the buffer is changed
		 * create compressed page table for audio firmware
		 * ret == 0 means the buffer is not changed
		 * so no need to regenerate the page table
		 */
		ret = create_page_table(substream, runtime->dma_area,
					runtime->dma_bytes);
		if (ret < 0)
			return ret;
	}

	/* number of pages should be rounded up */
	pcm.params.buffer.pages = PFN_UP(runtime->dma_bytes);

	/* set IPC PCM parameters */
	pcm.hdr.size = sizeof(pcm);
	pcm.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_PCM_PARAMS;
	pcm.comp_id = spcm->stream[substream->stream].comp_id;
	pcm.params.hdr.size = sizeof(pcm.params);
	pcm.params.buffer.phy_addr =
		spcm->stream[substream->stream].page_table.addr;
	pcm.params.buffer.size = runtime->dma_bytes;
	pcm.params.direction = substream->stream;
	pcm.params.sample_valid_bytes = params_width(params) >> 3;
	pcm.params.buffer_fmt = SOF_IPC_BUFFER_INTERLEAVED;
	pcm.params.rate = params_rate(params);
	pcm.params.channels = params_channels(params);
	pcm.params.host_period_bytes = params_period_bytes(params);

	/* container size */
	ret = snd_pcm_format_physical_width(params_format(params));
	if (ret < 0)
		return ret;
	pcm.params.sample_container_bytes = ret >> 3;

	/* format */
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
	case SNDRV_PCM_FORMAT_FLOAT:
		pcm.params.frame_fmt = SOF_IPC_FRAME_FLOAT;
		break;
	default:
		return -EINVAL;
	}

	/* firmware already configured host stream */
	ret = snd_sof_pcm_platform_hw_params(sdev,
					     substream,
					     params,
					     &pcm.params);
	if (ret < 0) {
		dev_err(sdev->dev, "error: platform hw params failed\n");
		return ret;
	}

	dev_dbg(sdev->dev, "stream_tag %d", pcm.params.stream_tag);

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, pcm.hdr.cmd, &pcm, sizeof(pcm),
				 &ipc_params_reply, sizeof(ipc_params_reply));
	if (ret < 0) {
		dev_err(sdev->dev, "error: hw params ipc failed for stream %d\n",
			pcm.params.stream_tag);
		return ret;
	}

	ret = sof_pcm_dsp_params(spcm, substream, &ipc_params_reply);
	if (ret < 0)
		return ret;

	spcm->prepared[substream->stream] = true;

	/* save pcm hw_params */
	memcpy(&spcm->params[substream->stream], params, sizeof(*params));

	return ret;
}