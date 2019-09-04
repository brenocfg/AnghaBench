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
 int /*<<< orphan*/  SKL_ADSPCS_CPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  SKL_ADSPCS_SPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  SKL_ADSP_REG_ADSPCS ; 
 int /*<<< orphan*/  SKL_DSP_PD_TO ; 
 int sst_dsp_register_poll (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int skl_dsp_core_power_down(struct sst_dsp  *ctx, unsigned int core_mask)
{
	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
				SKL_ADSPCS_SPA_MASK(core_mask), 0);

	/* poll with timeout to check if operation successful */
	return sst_dsp_register_poll(ctx,
			SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CPA_MASK(core_mask),
			0,
			SKL_DSP_PD_TO,
			"Power down");
}