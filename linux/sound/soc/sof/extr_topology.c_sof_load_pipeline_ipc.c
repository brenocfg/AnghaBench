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
struct TYPE_2__ {int cmd; int size; } ;
struct sof_ipc_pm_core_config {int core; int enable_mask; TYPE_1__ hdr; } ;
struct sof_ipc_pipe_new {int core; int enable_mask; TYPE_1__ hdr; } ;
struct sof_ipc_comp_reply {int core; int enable_mask; TYPE_1__ hdr; } ;
struct snd_sof_dev {int enabled_cores_mask; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
typedef  int /*<<< orphan*/  pm_core_config ;

/* Variables and functions */
 int SOF_IPC_GLB_PM_MSG ; 
 int SOF_IPC_PM_CORE_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct sof_ipc_pm_core_config*,int /*<<< orphan*/ ,int) ; 
 int snd_sof_dsp_core_power_up (struct snd_sof_dev*,int) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_pm_core_config*,int,struct sof_ipc_pm_core_config*,int) ; 

int sof_load_pipeline_ipc(struct snd_sof_dev *sdev,
			  struct sof_ipc_pipe_new *pipeline,
			  struct sof_ipc_comp_reply *r)
{
	struct sof_ipc_pm_core_config pm_core_config;
	int ret;

	ret = sof_ipc_tx_message(sdev->ipc, pipeline->hdr.cmd, pipeline,
				 sizeof(*pipeline), r, sizeof(*r));
	if (ret < 0) {
		dev_err(sdev->dev, "error: load pipeline ipc failure\n");
		return ret;
	}

	/* power up the core that this pipeline is scheduled on */
	ret = snd_sof_dsp_core_power_up(sdev, 1 << pipeline->core);
	if (ret < 0) {
		dev_err(sdev->dev, "error: powering up pipeline schedule core %d\n",
			pipeline->core);
		return ret;
	}

	/* update enabled cores mask */
	sdev->enabled_cores_mask |= 1 << pipeline->core;

	/*
	 * Now notify DSP that the core that this pipeline is scheduled on
	 * has been powered up
	 */
	memset(&pm_core_config, 0, sizeof(pm_core_config));
	pm_core_config.enable_mask = sdev->enabled_cores_mask;

	/* configure CORE_ENABLE ipc message */
	pm_core_config.hdr.size = sizeof(pm_core_config);
	pm_core_config.hdr.cmd = SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_CORE_ENABLE;

	/* send ipc */
	ret = sof_ipc_tx_message(sdev->ipc, pm_core_config.hdr.cmd,
				 &pm_core_config, sizeof(pm_core_config),
				 &pm_core_config, sizeof(pm_core_config));
	if (ret < 0)
		dev_err(sdev->dev, "error: core enable ipc failure\n");

	return ret;
}