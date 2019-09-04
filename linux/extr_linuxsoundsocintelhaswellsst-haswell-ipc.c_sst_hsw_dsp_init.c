#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct sst_pdata {struct sst_hsw* dsp; } ;
struct sst_hsw_ipc_fw_version {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  is_dsp_busy; int /*<<< orphan*/  reply_msg_match; int /*<<< orphan*/  tx_data_copy; int /*<<< orphan*/  shim_dbg; int /*<<< orphan*/  tx_msg; } ;
struct sst_generic_ipc {TYPE_2__* dsp; void* rx_data_max_size; void* tx_data_max_size; TYPE_1__ ops; struct device* dev; } ;
struct sst_hsw {TYPE_2__* dsp; int /*<<< orphan*/  dx_context_paddr; int /*<<< orphan*/ * dx_context; struct device* dev; int /*<<< orphan*/  boot_complete; int /*<<< orphan*/  boot_wait; int /*<<< orphan*/  stream_list; struct sst_generic_ipc ipc; } ;
struct device {int dummy; } ;
struct TYPE_13__ {struct sst_hsw* thread_context; } ;
struct TYPE_12__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPC_BOOT_MSECS ; 
 void* IPC_MAX_MAILBOX_BYTES ; 
 int /*<<< orphan*/  SST_HSW_DX_CONTEXT_SIZE ; 
 int /*<<< orphan*/  SST_HSW_MODULE_BASE_FW ; 
 int /*<<< orphan*/  SST_HSW_MODULE_WAVES ; 
 int /*<<< orphan*/  SST_IPCD ; 
 int /*<<< orphan*/  SST_IPCX ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sst_hsw* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__ hsw_dev ; 
 int /*<<< orphan*/  hsw_is_dsp_busy ; 
 int /*<<< orphan*/  hsw_reply_msg_match ; 
 int /*<<< orphan*/  hsw_shim_dbg ; 
 int /*<<< orphan*/  hsw_tx_data_copy ; 
 int /*<<< orphan*/  hsw_tx_msg ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sst_block_alloc_scratch (TYPE_2__*) ; 
 int /*<<< orphan*/  sst_dsp_boot (TYPE_2__*) ; 
 int /*<<< orphan*/  sst_dsp_free (TYPE_2__*) ; 
 TYPE_2__* sst_dsp_new (struct device*,TYPE_6__*,struct sst_pdata*) ; 
 int /*<<< orphan*/  sst_dsp_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  sst_dsp_shim_read_unlocked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_fw_free_all (TYPE_2__*) ; 
 int /*<<< orphan*/  sst_hsw_fw_get_version (struct sst_hsw*,struct sst_hsw_ipc_fw_version*) ; 
 int /*<<< orphan*/  sst_hsw_init_module_state (struct sst_hsw*) ; 
 int sst_hsw_mixer_get_info (struct sst_hsw*) ; 
 int sst_hsw_module_load (struct sst_hsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_hsw_reset_param_buf (struct sst_hsw*) ; 
 int /*<<< orphan*/  sst_ipc_fini (struct sst_generic_ipc*) ; 
 int sst_ipc_init (struct sst_generic_ipc*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sst_hsw_dsp_init(struct device *dev, struct sst_pdata *pdata)
{
	struct sst_hsw_ipc_fw_version version;
	struct sst_hsw *hsw;
	struct sst_generic_ipc *ipc;
	int ret;

	dev_dbg(dev, "initialising Audio DSP IPC\n");

	hsw = devm_kzalloc(dev, sizeof(*hsw), GFP_KERNEL);
	if (hsw == NULL)
		return -ENOMEM;

	hsw->dev = dev;

	ipc = &hsw->ipc;
	ipc->dev = dev;
	ipc->ops.tx_msg = hsw_tx_msg;
	ipc->ops.shim_dbg = hsw_shim_dbg;
	ipc->ops.tx_data_copy = hsw_tx_data_copy;
	ipc->ops.reply_msg_match = hsw_reply_msg_match;
	ipc->ops.is_dsp_busy = hsw_is_dsp_busy;

	ipc->tx_data_max_size = IPC_MAX_MAILBOX_BYTES;
	ipc->rx_data_max_size = IPC_MAX_MAILBOX_BYTES;

	ret = sst_ipc_init(ipc);
	if (ret != 0)
		goto ipc_init_err;

	INIT_LIST_HEAD(&hsw->stream_list);
	init_waitqueue_head(&hsw->boot_wait);
	hsw_dev.thread_context = hsw;

	/* init SST shim */
	hsw->dsp = sst_dsp_new(dev, &hsw_dev, pdata);
	if (hsw->dsp == NULL) {
		ret = -ENODEV;
		goto dsp_new_err;
	}

	ipc->dsp = hsw->dsp;

	/* allocate DMA buffer for context storage */
	hsw->dx_context = dma_alloc_coherent(hsw->dsp->dma_dev,
		SST_HSW_DX_CONTEXT_SIZE, &hsw->dx_context_paddr, GFP_KERNEL);
	if (hsw->dx_context == NULL) {
		ret = -ENOMEM;
		goto dma_err;
	}

	/* keep the DSP in reset state for base FW loading */
	sst_dsp_reset(hsw->dsp);

	/* load base module and other modules in base firmware image */
	ret = sst_hsw_module_load(hsw, SST_HSW_MODULE_BASE_FW, 0, "Base");
	if (ret < 0)
		goto fw_err;

	/* try to load module waves */
	sst_hsw_module_load(hsw, SST_HSW_MODULE_WAVES, 0, "intel/IntcPP01.bin");

	/* allocate scratch mem regions */
	ret = sst_block_alloc_scratch(hsw->dsp);
	if (ret < 0)
		goto boot_err;

	/* init param buffer */
	sst_hsw_reset_param_buf(hsw);

	/* wait for DSP boot completion */
	sst_dsp_boot(hsw->dsp);
	ret = wait_event_timeout(hsw->boot_wait, hsw->boot_complete,
		msecs_to_jiffies(IPC_BOOT_MSECS));
	if (ret == 0) {
		ret = -EIO;
		dev_err(hsw->dev, "error: audio DSP boot timeout IPCD 0x%x IPCX 0x%x\n",
			sst_dsp_shim_read_unlocked(hsw->dsp, SST_IPCD),
			sst_dsp_shim_read_unlocked(hsw->dsp, SST_IPCX));
		goto boot_err;
	}

	/* init module state after boot */
	sst_hsw_init_module_state(hsw);

	/* get the FW version */
	sst_hsw_fw_get_version(hsw, &version);

	/* get the globalmixer */
	ret = sst_hsw_mixer_get_info(hsw);
	if (ret < 0) {
		dev_err(hsw->dev, "error: failed to get stream info\n");
		goto boot_err;
	}

	pdata->dsp = hsw;
	return 0;

boot_err:
	sst_dsp_reset(hsw->dsp);
	sst_fw_free_all(hsw->dsp);
fw_err:
	dma_free_coherent(hsw->dsp->dma_dev, SST_HSW_DX_CONTEXT_SIZE,
			hsw->dx_context, hsw->dx_context_paddr);
dma_err:
	sst_dsp_free(hsw->dsp);
dsp_new_err:
	sst_ipc_fini(ipc);
ipc_init_err:
	return ret;
}