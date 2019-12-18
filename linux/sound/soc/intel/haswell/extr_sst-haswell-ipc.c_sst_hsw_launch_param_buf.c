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
struct sst_hsw {int param_idx_w; int /*<<< orphan*/ ** param_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_HSW_MODULE_WAVES ; 
 int /*<<< orphan*/  WAVES_PARAM_COUNT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_hsw_is_module_active (struct sst_hsw*,int /*<<< orphan*/ ) ; 
 int sst_hsw_module_set_param (struct sst_hsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sst_hsw_launch_param_buf(struct sst_hsw *hsw)
{
	int ret, idx;

	if (!sst_hsw_is_module_active(hsw, SST_HSW_MODULE_WAVES)) {
		dev_dbg(hsw->dev, "module waves is not active\n");
		return 0;
	}

	/* put all param lines to DSP through ipc */
	for (idx = 0; idx < hsw->param_idx_w; idx++) {
		ret = sst_hsw_module_set_param(hsw,
			SST_HSW_MODULE_WAVES, 0, hsw->param_buf[idx][0],
			WAVES_PARAM_COUNT, hsw->param_buf[idx]);
		if (ret < 0)
			return ret;
	}
	return 0;
}