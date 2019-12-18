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
 int cnl_dsp_core_power_up (struct sst_dsp*,unsigned int) ; 
 int cnl_dsp_start_core (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 

int cnl_dsp_enable_core(struct sst_dsp *ctx, unsigned int core_mask)
{
	int ret;

	/* power up */
	ret = cnl_dsp_core_power_up(ctx, core_mask);
	if (ret < 0) {
		dev_dbg(ctx->dev, "DSP core mask %#x power up failed",
			core_mask);
		return ret;
	}

	return cnl_dsp_start_core(ctx, core_mask);
}