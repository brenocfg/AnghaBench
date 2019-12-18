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
struct sst_byt {int /*<<< orphan*/  fw; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; int /*<<< orphan*/  dsp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_dsp_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_fw_unload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_ipc_drop_all (int /*<<< orphan*/ *) ; 

int sst_byt_dsp_suspend_late(struct device *dev, struct sst_pdata *pdata)
{
	struct sst_byt *byt = pdata->dsp;

	dev_dbg(byt->dev, "dsp reset\n");
	sst_dsp_reset(byt->dsp);
	sst_ipc_drop_all(&byt->ipc);
	dev_dbg(byt->dev, "dsp in reset\n");

	dev_dbg(byt->dev, "free all blocks and unload fw\n");
	sst_fw_unload(byt->fw);

	return 0;
}