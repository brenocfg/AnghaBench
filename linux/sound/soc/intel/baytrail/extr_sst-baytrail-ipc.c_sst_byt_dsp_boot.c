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
struct sst_pdata {struct sst_byt* dsp; } ;
struct sst_byt {int boot_complete; int /*<<< orphan*/  dev; int /*<<< orphan*/  dsp; int /*<<< orphan*/  fw; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  sst_dsp_boot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_reset (int /*<<< orphan*/ ) ; 
 int sst_fw_reload (int /*<<< orphan*/ ) ; 

int sst_byt_dsp_boot(struct device *dev, struct sst_pdata *pdata)
{
	struct sst_byt *byt = pdata->dsp;
	int ret;

	dev_dbg(byt->dev, "reload dsp fw\n");

	sst_dsp_reset(byt->dsp);

	ret = sst_fw_reload(byt->fw);
	if (ret <  0) {
		dev_err(dev, "error: failed to reload firmware\n");
		return ret;
	}

	/* wait for DSP boot completion */
	byt->boot_complete = false;
	sst_dsp_boot(byt->dsp);
	dev_dbg(byt->dev, "dsp booting...\n");

	return 0;
}