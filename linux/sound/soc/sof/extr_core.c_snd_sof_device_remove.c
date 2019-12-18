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
struct snd_sof_pdata {int /*<<< orphan*/ * fw; int /*<<< orphan*/  pdev_mach; } ;
struct snd_sof_dev {int /*<<< orphan*/  probe_work; struct snd_sof_pdata* pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_SOC_SOF_PROBE_WORK_QUEUE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct snd_sof_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sof_free_debug (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_free_trace (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_fw_unload (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_ipc_free (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_remove (struct snd_sof_dev*) ; 

int snd_sof_device_remove(struct device *dev)
{
	struct snd_sof_dev *sdev = dev_get_drvdata(dev);
	struct snd_sof_pdata *pdata = sdev->pdata;

	if (IS_ENABLED(CONFIG_SND_SOC_SOF_PROBE_WORK_QUEUE))
		cancel_work_sync(&sdev->probe_work);

	snd_sof_fw_unload(sdev);
	snd_sof_ipc_free(sdev);
	snd_sof_free_debug(sdev);
	snd_sof_free_trace(sdev);

	/*
	 * Unregister machine driver. This will unbind the snd_card which
	 * will remove the component driver and unload the topology
	 * before freeing the snd_card.
	 */
	if (!IS_ERR_OR_NULL(pdata->pdev_mach))
		platform_device_unregister(pdata->pdev_mach);

	/*
	 * Unregistering the machine driver results in unloading the topology.
	 * Some widgets, ex: scheduler, attempt to power down the core they are
	 * scheduled on, when they are unloaded. Therefore, the DSP must be
	 * removed only after the topology has been unloaded.
	 */
	snd_sof_remove(sdev);

	/* release firmware */
	release_firmware(pdata->fw);
	pdata->fw = NULL;

	return 0;
}