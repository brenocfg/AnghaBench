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
typedef  int u64 ;
struct nau8810_pll {int mclk_scaler; int pre_factor; int pll_int; int pll_frac; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long long*) ; 
 int EINVAL ; 
 int NAU_PLL_FREQ_MAX ; 
 int NAU_PLL_FREQ_MIN ; 
 int NAU_PLL_OPTOP_MIN ; 
 unsigned int NAU_PLL_REF_MAX ; 
 unsigned int NAU_PLL_REF_MIN ; 
 int div_u64 (int,unsigned int) ; 
 unsigned long long* nau8810_mclk_scaler ; 

__attribute__((used)) static int nau8810_calc_pll(unsigned int pll_in,
	unsigned int fs, struct nau8810_pll *pll_param)
{
	u64 f2, f2_max, pll_ratio;
	int i, scal_sel;

	if (pll_in > NAU_PLL_REF_MAX || pll_in < NAU_PLL_REF_MIN)
		return -EINVAL;

	f2_max = 0;
	scal_sel = ARRAY_SIZE(nau8810_mclk_scaler);
	for (i = 0; i < ARRAY_SIZE(nau8810_mclk_scaler); i++) {
		f2 = 256ULL * fs * 4 * nau8810_mclk_scaler[i];
		f2 = div_u64(f2, 10);
		if (f2 > NAU_PLL_FREQ_MIN && f2 < NAU_PLL_FREQ_MAX &&
			f2_max < f2) {
			f2_max = f2;
			scal_sel = i;
		}
	}
	if (ARRAY_SIZE(nau8810_mclk_scaler) == scal_sel)
		return -EINVAL;
	pll_param->mclk_scaler = scal_sel;
	f2 = f2_max;

	/* Calculate the PLL 4-bit integer input and the PLL 24-bit fractional
	 * input; round up the 24+4bit.
	 */
	pll_ratio = div_u64(f2 << 28, pll_in);
	pll_param->pre_factor = 0;
	if (((pll_ratio >> 28) & 0xF) < NAU_PLL_OPTOP_MIN) {
		pll_ratio <<= 1;
		pll_param->pre_factor = 1;
	}
	pll_param->pll_int = (pll_ratio >> 28) & 0xF;
	pll_param->pll_frac = ((pll_ratio & 0xFFFFFFF) >> 4);

	return 0;
}