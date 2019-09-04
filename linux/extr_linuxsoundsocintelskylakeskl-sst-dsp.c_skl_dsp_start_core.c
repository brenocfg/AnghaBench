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
 int /*<<< orphan*/  SKL_ADSPCS_CSTALL_MASK (unsigned int) ; 
 int /*<<< orphan*/  SKL_ADSP_REG_ADSPCS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  is_skl_dsp_core_enable (struct sst_dsp*,unsigned int) ; 
 int skl_dsp_core_unset_reset_state (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  skl_dsp_reset_core (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int skl_dsp_start_core(struct sst_dsp *ctx, unsigned int core_mask)
{
	int ret;

	/* unset reset state */
	ret = skl_dsp_core_unset_reset_state(ctx, core_mask);
	if (ret < 0)
		return ret;

	/* run core */
	dev_dbg(ctx->dev, "unstall/run core: core_mask = %x\n", core_mask);
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CSTALL_MASK(core_mask), 0);

	if (!is_skl_dsp_core_enable(ctx, core_mask)) {
		skl_dsp_reset_core(ctx, core_mask);
		dev_err(ctx->dev, "DSP start core failed: core_mask %x\n",
							core_mask);
		ret = -EIO;
	}

	return ret;
}