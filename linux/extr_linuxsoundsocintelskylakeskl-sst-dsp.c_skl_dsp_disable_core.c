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
struct sst_dsp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ is_skl_dsp_core_enable (struct sst_dsp*,unsigned int) ; 
 int skl_dsp_core_power_down (struct sst_dsp*,unsigned int) ; 
 int skl_dsp_reset_core (struct sst_dsp*,unsigned int) ; 

int skl_dsp_disable_core(struct sst_dsp *ctx, unsigned int core_mask)
{
	int ret;

	ret = skl_dsp_reset_core(ctx, core_mask);
	if (ret < 0) {
		dev_err(ctx->dev, "dsp core reset failed: core_mask %x\n",
							core_mask);
		return ret;
	}

	/* power down core*/
	ret = skl_dsp_core_power_down(ctx, core_mask);
	if (ret < 0) {
		dev_err(ctx->dev, "dsp core power down fail mask %x: %d\n",
							core_mask, ret);
		return ret;
	}

	if (is_skl_dsp_core_enable(ctx, core_mask)) {
		dev_err(ctx->dev, "dsp core disable fail mask %x: %d\n",
							core_mask, ret);
		ret = -EIO;
	}

	return ret;
}