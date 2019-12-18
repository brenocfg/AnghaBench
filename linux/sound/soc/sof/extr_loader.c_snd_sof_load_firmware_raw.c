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
struct snd_sof_pdata {scalar_t__ fw; int /*<<< orphan*/  fw_filename; int /*<<< orphan*/  fw_filename_prefix; } ;
struct snd_sof_dev {int code_loading; int /*<<< orphan*/  dev; struct snd_sof_pdata* pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int request_firmware (scalar_t__*,char const*,int /*<<< orphan*/ ) ; 

int snd_sof_load_firmware_raw(struct snd_sof_dev *sdev)
{
	struct snd_sof_pdata *plat_data = sdev->pdata;
	const char *fw_filename;
	int ret;

	/* set code loading condition to true */
	sdev->code_loading = 1;

	/* Don't request firmware again if firmware is already requested */
	if (plat_data->fw)
		return 0;

	fw_filename = kasprintf(GFP_KERNEL, "%s/%s",
				plat_data->fw_filename_prefix,
				plat_data->fw_filename);
	if (!fw_filename)
		return -ENOMEM;

	ret = request_firmware(&plat_data->fw, fw_filename, sdev->dev);

	if (ret < 0) {
		dev_err(sdev->dev, "error: request firmware %s failed err: %d\n",
			fw_filename, ret);
	}

	kfree(fw_filename);

	return ret;
}