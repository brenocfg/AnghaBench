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
struct snd_sof_dev {int boot_complete; int enabled_cores_mask; int /*<<< orphan*/  dev; int /*<<< orphan*/  boot_timeout; int /*<<< orphan*/  boot_wait; int /*<<< orphan*/  fw_version; scalar_t__ first_boot; } ;

/* Variables and functions */
 int EIO ; 
 int SOF_DBG_MBOX ; 
 int SOF_DBG_PCI ; 
 int SOF_DBG_REGS ; 
 int SOF_DBG_TEXT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int snd_sof_debugfs_buf_item (struct snd_sof_dev*,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_dbg_dump (struct snd_sof_dev*,int) ; 
 int snd_sof_dsp_post_fw_run (struct snd_sof_dev*) ; 
 int snd_sof_dsp_pre_fw_run (struct snd_sof_dev*) ; 
 int snd_sof_dsp_run (struct snd_sof_dev*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int snd_sof_run_firmware(struct snd_sof_dev *sdev)
{
	int ret;
	int init_core_mask;

	init_waitqueue_head(&sdev->boot_wait);
	sdev->boot_complete = false;

	/* create read-only fw_version debugfs to store boot version info */
	if (sdev->first_boot) {
		ret = snd_sof_debugfs_buf_item(sdev, &sdev->fw_version,
					       sizeof(sdev->fw_version),
					       "fw_version", 0444);
		/* errors are only due to memory allocation, not debugfs */
		if (ret < 0) {
			dev_err(sdev->dev, "error: snd_sof_debugfs_buf_item failed\n");
			return ret;
		}
	}

	/* perform pre fw run operations */
	ret = snd_sof_dsp_pre_fw_run(sdev);
	if (ret < 0) {
		dev_err(sdev->dev, "error: failed pre fw run op\n");
		return ret;
	}

	dev_dbg(sdev->dev, "booting DSP firmware\n");

	/* boot the firmware on the DSP */
	ret = snd_sof_dsp_run(sdev);
	if (ret < 0) {
		dev_err(sdev->dev, "error: failed to reset DSP\n");
		return ret;
	}

	init_core_mask = ret;

	/* now wait for the DSP to boot */
	ret = wait_event_timeout(sdev->boot_wait, sdev->boot_complete,
				 msecs_to_jiffies(sdev->boot_timeout));
	if (ret == 0) {
		dev_err(sdev->dev, "error: firmware boot failure\n");
		snd_sof_dsp_dbg_dump(sdev, SOF_DBG_REGS | SOF_DBG_MBOX |
			SOF_DBG_TEXT | SOF_DBG_PCI);
		/* after this point FW_READY msg should be ignored */
		sdev->boot_complete = true;
		return -EIO;
	}

	dev_info(sdev->dev, "firmware boot complete\n");

	/* perform post fw run operations */
	ret = snd_sof_dsp_post_fw_run(sdev);
	if (ret < 0) {
		dev_err(sdev->dev, "error: failed post fw run op\n");
		return ret;
	}

	/* fw boot is complete. Update the active cores mask */
	sdev->enabled_cores_mask = init_core_mask;

	return 0;
}