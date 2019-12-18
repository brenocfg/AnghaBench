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
struct snd_sof_pdata {int /*<<< orphan*/ * fw; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; struct snd_sof_pdata* pdata; } ;

/* Variables and functions */
 int check_header (struct snd_sof_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int load_modules (struct snd_sof_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int snd_sof_dsp_reset (struct snd_sof_dev*) ; 
 int snd_sof_load_firmware_raw (struct snd_sof_dev*) ; 

int snd_sof_load_firmware_memcpy(struct snd_sof_dev *sdev)
{
	struct snd_sof_pdata *plat_data = sdev->pdata;
	int ret;

	ret = snd_sof_load_firmware_raw(sdev);
	if (ret < 0)
		return ret;

	/* make sure the FW header and file is valid */
	ret = check_header(sdev, plat_data->fw);
	if (ret < 0) {
		dev_err(sdev->dev, "error: invalid FW header\n");
		goto error;
	}

	/* prepare the DSP for FW loading */
	ret = snd_sof_dsp_reset(sdev);
	if (ret < 0) {
		dev_err(sdev->dev, "error: failed to reset DSP\n");
		goto error;
	}

	/* parse and load firmware modules to DSP */
	ret = load_modules(sdev, plat_data->fw);
	if (ret < 0) {
		dev_err(sdev->dev, "error: invalid FW modules\n");
		goto error;
	}

	return 0;

error:
	release_firmware(plat_data->fw);
	plat_data->fw = NULL;
	return ret;

}