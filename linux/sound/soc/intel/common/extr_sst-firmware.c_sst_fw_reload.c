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
struct sst_fw {struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* parse_fw ) (struct sst_fw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct sst_fw*) ; 

int sst_fw_reload(struct sst_fw *sst_fw)
{
	struct sst_dsp *dsp = sst_fw->dsp;
	int ret;

	dev_dbg(dsp->dev, "reloading firmware\n");

	/* call core specific FW paser to load FW data into DSP */
	ret = dsp->ops->parse_fw(sst_fw);
	if (ret < 0)
		dev_err(dsp->dev, "error: parse fw failed %d\n", ret);

	return ret;
}