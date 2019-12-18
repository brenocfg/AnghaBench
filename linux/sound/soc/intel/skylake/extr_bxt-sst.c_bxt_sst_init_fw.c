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
struct TYPE_2__ {int (* load_fw ) (struct sst_dsp*) ;int (* load_library ) (struct sst_dsp*,int /*<<< orphan*/ ,int) ;} ;
struct sst_dsp {TYPE_1__ fw_ops; } ;
struct skl_dev {int lib_count; int is_first_boot; int /*<<< orphan*/  lib_info; struct sst_dsp* dsp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  skl_dsp_init_core_state (struct sst_dsp*) ; 
 int stub1 (struct sst_dsp*) ; 
 int stub2 (struct sst_dsp*,int /*<<< orphan*/ ,int) ; 

int bxt_sst_init_fw(struct device *dev, struct skl_dev *skl)
{
	int ret;
	struct sst_dsp *sst = skl->dsp;

	ret = sst->fw_ops.load_fw(sst);
	if (ret < 0) {
		dev_err(dev, "Load base fw failed: %x\n", ret);
		return ret;
	}

	skl_dsp_init_core_state(sst);

	if (skl->lib_count > 1) {
		ret = sst->fw_ops.load_library(sst, skl->lib_info,
						skl->lib_count);
		if (ret < 0) {
			dev_err(dev, "Load Library failed : %x\n", ret);
			return ret;
		}
	}
	skl->is_first_boot = false;

	return 0;
}