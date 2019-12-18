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
 int cnl_dsp_core_power_down (struct sst_dsp*,unsigned int) ; 
 int cnl_dsp_reset_core (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ is_cnl_dsp_core_enable (struct sst_dsp*,unsigned int) ; 

int cnl_dsp_disable_core(struct sst_dsp *ctx, unsigned int core_mask)
{
	int ret;

	ret = cnl_dsp_reset_core(ctx, core_mask);
	if (ret < 0) {
		dev_err(ctx->dev, "DSP core mask %#x reset failed\n",
			core_mask);
		return ret;
	}

	/* power down core*/
	ret = cnl_dsp_core_power_down(ctx, core_mask);
	if (ret < 0) {
		dev_err(ctx->dev, "DSP core mask %#x power down failed\n",
			core_mask);
		return ret;
	}

	if (is_cnl_dsp_core_enable(ctx, core_mask)) {
		dev_err(ctx->dev, "DSP core mask %#x disable failed\n",
			core_mask);
		ret = -EIO;
	}

	return ret;
}