#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct nau8824_fll {unsigned int clk_ref_div; unsigned int ratio; unsigned int mclk_src; int fll_int; int fll_frac; } ;
struct TYPE_5__ {unsigned int param; unsigned int val; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 unsigned int NAU_FREF_MAX ; 
 int NAU_FVCO_MAX ; 
 int NAU_FVCO_MIN ; 
 int div_u64 (int,unsigned int) ; 
 TYPE_1__* fll_pre_scalar ; 
 TYPE_1__* fll_ratio ; 
 TYPE_1__* mclk_src_scaling ; 

__attribute__((used)) static int nau8824_calc_fll_param(unsigned int fll_in,
	unsigned int fs, struct nau8824_fll *fll_param)
{
	u64 fvco, fvco_max;
	unsigned int fref, i, fvco_sel;

	/* Ensure the reference clock frequency (FREF) is <= 13.5MHz by dividing
	 * freq_in by 1, 2, 4, or 8 using FLL pre-scalar.
	 * FREF = freq_in / NAU8824_FLL_REF_DIV_MASK
	 */
	for (i = 0; i < ARRAY_SIZE(fll_pre_scalar); i++) {
		fref = fll_in / fll_pre_scalar[i].param;
		if (fref <= NAU_FREF_MAX)
			break;
	}
	if (i == ARRAY_SIZE(fll_pre_scalar))
		return -EINVAL;
	fll_param->clk_ref_div = fll_pre_scalar[i].val;

	/* Choose the FLL ratio based on FREF */
	for (i = 0; i < ARRAY_SIZE(fll_ratio); i++) {
		if (fref >= fll_ratio[i].param)
			break;
	}
	if (i == ARRAY_SIZE(fll_ratio))
		return -EINVAL;
	fll_param->ratio = fll_ratio[i].val;

	/* Calculate the frequency of DCO (FDCO) given freq_out = 256 * Fs.
	 * FDCO must be within the 90MHz - 124MHz or the FFL cannot be
	 * guaranteed across the full range of operation.
	 * FDCO = freq_out * 2 * mclk_src_scaling
	 */
	fvco_max = 0;
	fvco_sel = ARRAY_SIZE(mclk_src_scaling);
	for (i = 0; i < ARRAY_SIZE(mclk_src_scaling); i++) {
		fvco = 256ULL * fs * 2 * mclk_src_scaling[i].param;
		if (fvco > NAU_FVCO_MIN && fvco < NAU_FVCO_MAX &&
			fvco_max < fvco) {
			fvco_max = fvco;
			fvco_sel = i;
		}
	}
	if (ARRAY_SIZE(mclk_src_scaling) == fvco_sel)
		return -EINVAL;
	fll_param->mclk_src = mclk_src_scaling[fvco_sel].val;

	/* Calculate the FLL 10-bit integer input and the FLL 16-bit fractional
	 * input based on FDCO, FREF and FLL ratio.
	 */
	fvco = div_u64(fvco_max << 16, fref * fll_param->ratio);
	fll_param->fll_int = (fvco >> 16) & 0x3FF;
	fll_param->fll_frac = fvco & 0xFFFF;
	return 0;
}