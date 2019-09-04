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
 int /*<<< orphan*/  CNL_ADSPCS_CSTALL (unsigned int) ; 
 int /*<<< orphan*/  CNL_ADSP_REG_ADSPCS ; 
 int EIO ; 
 int cnl_dsp_core_unset_reset_state (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  cnl_dsp_reset_core (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  is_cnl_dsp_core_enable (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnl_dsp_start_core(struct sst_dsp *ctx, unsigned int core_mask)
{
	int ret;

	/* unset reset state */
	ret = cnl_dsp_core_unset_reset_state(ctx, core_mask);
	if (ret < 0)
		return ret;

	/* run core */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
				CNL_ADSPCS_CSTALL(core_mask), 0);

	if (!is_cnl_dsp_core_enable(ctx, core_mask)) {
		cnl_dsp_reset_core(ctx, core_mask);
		dev_err(ctx->dev, "DSP core mask %#x enable failed\n",
			core_mask);
		ret = -EIO;
	}

	return ret;
}