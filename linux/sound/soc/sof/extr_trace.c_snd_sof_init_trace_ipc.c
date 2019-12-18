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
struct sof_ipc_reply {int dummy; } ;
struct sof_ipc_fw_version {scalar_t__ abi_version; } ;
struct sof_ipc_fw_ready {struct sof_ipc_fw_version version; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  cmd; } ;
struct TYPE_7__ {scalar_t__ pages; int /*<<< orphan*/  size; int /*<<< orphan*/  phy_addr; } ;
struct sof_ipc_dma_trace_params_ext {TYPE_4__ hdr; scalar_t__ stream_tag; TYPE_3__ buffer; int /*<<< orphan*/  timestamp_ns; } ;
struct sof_ipc_dma_trace_params {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct snd_sof_dev {int dtrace_is_enabled; int dtrace_draining; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; scalar_t__ host_offset; scalar_t__ dma_trace_pages; TYPE_2__ dmatb; TYPE_1__ dmatp; struct sof_ipc_fw_ready fw_ready; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  ipc_reply ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_START ; 
 scalar_t__ SOF_ABI_VER (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOF_IPC_GLB_TRACE_MSG ; 
 int /*<<< orphan*/  SOF_IPC_TRACE_DMA_PARAMS ; 
 int /*<<< orphan*/  SOF_IPC_TRACE_DMA_PARAMS_EXT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int snd_sof_dma_trace_init (struct snd_sof_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  snd_sof_dma_trace_release (struct snd_sof_dev*) ; 
 int snd_sof_dma_trace_trigger (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sof_ipc_dma_trace_params_ext*,int,struct sof_ipc_reply*,int) ; 

int snd_sof_init_trace_ipc(struct snd_sof_dev *sdev)
{
	struct sof_ipc_fw_ready *ready = &sdev->fw_ready;
	struct sof_ipc_fw_version *v = &ready->version;
	struct sof_ipc_dma_trace_params_ext params;
	struct sof_ipc_reply ipc_reply;
	int ret;

	if (sdev->dtrace_is_enabled || !sdev->dma_trace_pages)
		return -EINVAL;

	/* set IPC parameters */
	params.hdr.cmd = SOF_IPC_GLB_TRACE_MSG;
	/* PARAMS_EXT is only supported from ABI 3.7.0 onwards */
	if (v->abi_version >= SOF_ABI_VER(3, 7, 0)) {
		params.hdr.size = sizeof(struct sof_ipc_dma_trace_params_ext);
		params.hdr.cmd |= SOF_IPC_TRACE_DMA_PARAMS_EXT;
		params.timestamp_ns = ktime_get(); /* in nanosecond */
	} else {
		params.hdr.size = sizeof(struct sof_ipc_dma_trace_params);
		params.hdr.cmd |= SOF_IPC_TRACE_DMA_PARAMS;
	}
	params.buffer.phy_addr = sdev->dmatp.addr;
	params.buffer.size = sdev->dmatb.bytes;
	params.buffer.pages = sdev->dma_trace_pages;
	params.stream_tag = 0;

	sdev->host_offset = 0;
	sdev->dtrace_draining = false;

	ret = snd_sof_dma_trace_init(sdev, &params.stream_tag);
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: fail in snd_sof_dma_trace_init %d\n", ret);
		return ret;
	}
	dev_dbg(sdev->dev, "stream_tag: %d\n", params.stream_tag);

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc,
				 params.hdr.cmd, &params, sizeof(params),
				 &ipc_reply, sizeof(ipc_reply));
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: can't set params for DMA for trace %d\n", ret);
		goto trace_release;
	}

	ret = snd_sof_dma_trace_trigger(sdev, SNDRV_PCM_TRIGGER_START);
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: snd_sof_dma_trace_trigger: start: %d\n", ret);
		goto trace_release;
	}

	sdev->dtrace_is_enabled = true;

	return 0;

trace_release:
	snd_sof_dma_trace_release(sdev);
	return ret;
}