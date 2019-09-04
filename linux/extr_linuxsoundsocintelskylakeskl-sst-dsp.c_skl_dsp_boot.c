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
 int /*<<< orphan*/  SKL_DSP_CORE0_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_skl_dsp_core_enable (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_dsp_disable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_dsp_enable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_dsp_reset_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_dsp_start_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 

int skl_dsp_boot(struct sst_dsp *ctx)
{
	int ret;

	if (is_skl_dsp_core_enable(ctx, SKL_DSP_CORE0_MASK)) {
		ret = skl_dsp_reset_core(ctx, SKL_DSP_CORE0_MASK);
		if (ret < 0) {
			dev_err(ctx->dev, "dsp core0 reset fail: %d\n", ret);
			return ret;
		}

		ret = skl_dsp_start_core(ctx, SKL_DSP_CORE0_MASK);
		if (ret < 0) {
			dev_err(ctx->dev, "dsp core0 start fail: %d\n", ret);
			return ret;
		}
	} else {
		ret = skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
		if (ret < 0) {
			dev_err(ctx->dev, "dsp core0 disable fail: %d\n", ret);
			return ret;
		}
		ret = skl_dsp_enable_core(ctx, SKL_DSP_CORE0_MASK);
	}

	return ret;
}