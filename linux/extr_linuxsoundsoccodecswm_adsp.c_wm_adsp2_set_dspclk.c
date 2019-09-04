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
struct wm_adsp {int rev; scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADSP2_CLK_SEL_MASK ; 
 unsigned int ADSP2_CLK_SEL_SHIFT ; 
 scalar_t__ ADSP2_CLOCKING ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int regmap_update_bits_async (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void wm_adsp2_set_dspclk(struct wm_adsp *dsp, unsigned int freq)
{
	int ret;

	switch (dsp->rev) {
	case 0:
		ret = regmap_update_bits_async(dsp->regmap,
					       dsp->base + ADSP2_CLOCKING,
					       ADSP2_CLK_SEL_MASK,
					       freq << ADSP2_CLK_SEL_SHIFT);
		if (ret) {
			adsp_err(dsp, "Failed to set clock rate: %d\n", ret);
			return;
		}
		break;
	default:
		/* clock is handled by parent codec driver */
		break;
	}
}