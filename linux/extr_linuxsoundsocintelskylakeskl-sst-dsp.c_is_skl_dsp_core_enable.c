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
 int SKL_ADSPCS_CPA_MASK (unsigned int) ; 
 int SKL_ADSPCS_CRST_MASK (unsigned int) ; 
 int SKL_ADSPCS_CSTALL_MASK (unsigned int) ; 
 int SKL_ADSPCS_SPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  SKL_ADSP_REG_ADSPCS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_skl_dsp_core_enable(struct sst_dsp *ctx, unsigned int core_mask)
{
	int val;
	bool is_enable;

	val = sst_dsp_shim_read_unlocked(ctx, SKL_ADSP_REG_ADSPCS);

	is_enable = ((val & SKL_ADSPCS_CPA_MASK(core_mask)) &&
			(val & SKL_ADSPCS_SPA_MASK(core_mask)) &&
			!(val & SKL_ADSPCS_CRST_MASK(core_mask)) &&
			!(val & SKL_ADSPCS_CSTALL_MASK(core_mask)));

	dev_dbg(ctx->dev, "DSP core(s) enabled? %d : core_mask %x\n",
						is_enable, core_mask);

	return is_enable;
}