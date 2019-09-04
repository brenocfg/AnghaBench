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
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_ADSPCS_CSTALL (unsigned int) ; 
 int /*<<< orphan*/  CNL_ADSP_REG_ADSPCS ; 
 int cnl_dsp_core_set_reset_state (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnl_dsp_reset_core(struct sst_dsp *ctx, unsigned int core_mask)
{
	/* stall core */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
			CNL_ADSPCS_CSTALL(core_mask),
			CNL_ADSPCS_CSTALL(core_mask));

	/* set reset state */
	return cnl_dsp_core_set_reset_state(ctx, core_mask);
}