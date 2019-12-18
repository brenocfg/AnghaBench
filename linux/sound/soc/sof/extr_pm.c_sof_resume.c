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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_resume; int /*<<< orphan*/  resume; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOF_IPC_PM_CTX_RESTORE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_sof_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int snd_sof_dsp_resume (struct snd_sof_dev*) ; 
 int snd_sof_dsp_runtime_resume (struct snd_sof_dev*) ; 
 int snd_sof_init_trace_ipc (struct snd_sof_dev*) ; 
 int snd_sof_load_firmware (struct snd_sof_dev*) ; 
 int snd_sof_run_firmware (struct snd_sof_dev*) ; 
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 int sof_restore_pipelines (struct snd_sof_dev*) ; 
 int sof_send_pm_ipc (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sof_resume(struct device *dev, bool runtime_resume)
{
	struct snd_sof_dev *sdev = dev_get_drvdata(dev);
	int ret;

	/* do nothing if dsp resume callbacks are not set */
	if (!sof_ops(sdev)->resume || !sof_ops(sdev)->runtime_resume)
		return 0;

	/*
	 * if the runtime_resume flag is set, call the runtime_resume routine
	 * or else call the system resume routine
	 */
	if (runtime_resume)
		ret = snd_sof_dsp_runtime_resume(sdev);
	else
		ret = snd_sof_dsp_resume(sdev);
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: failed to power up DSP after resume\n");
		return ret;
	}

	/* load the firmware */
	ret = snd_sof_load_firmware(sdev);
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: failed to load DSP firmware after resume %d\n",
			ret);
		return ret;
	}

	/* boot the firmware */
	ret = snd_sof_run_firmware(sdev);
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: failed to boot DSP firmware after resume %d\n",
			ret);
		return ret;
	}

	/* resume DMA trace, only need send ipc */
	ret = snd_sof_init_trace_ipc(sdev);
	if (ret < 0) {
		/* non fatal */
		dev_warn(sdev->dev,
			 "warning: failed to init trace after resume %d\n",
			 ret);
	}

	/* restore pipelines */
	ret = sof_restore_pipelines(sdev);
	if (ret < 0) {
		dev_err(sdev->dev,
			"error: failed to restore pipeline after resume %d\n",
			ret);
		return ret;
	}

	/* notify DSP of system resume */
	ret = sof_send_pm_ipc(sdev, SOF_IPC_PM_CTX_RESTORE);
	if (ret < 0)
		dev_err(sdev->dev,
			"error: ctx_restore ipc error during resume %d\n",
			ret);

	return ret;
}