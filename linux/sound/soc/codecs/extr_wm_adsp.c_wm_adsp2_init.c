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
struct wm_adsp {int rev; int /*<<< orphan*/  boot_work; int /*<<< orphan*/ * ops; scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADSP2_CONTROL ; 
 int /*<<< orphan*/  ADSP2_MEM_ENA ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wm_adsp2_ops ; 
 int /*<<< orphan*/  wm_adsp_boot_work ; 
 int wm_adsp_common_init (struct wm_adsp*) ; 

int wm_adsp2_init(struct wm_adsp *dsp)
{
	int ret;

	ret = wm_adsp_common_init(dsp);
	if (ret)
		return ret;

	switch (dsp->rev) {
	case 0:
		/*
		 * Disable the DSP memory by default when in reset for a small
		 * power saving.
		 */
		ret = regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
					 ADSP2_MEM_ENA, 0);
		if (ret) {
			adsp_err(dsp,
				 "Failed to clear memory retention: %d\n", ret);
			return ret;
		}

		dsp->ops = &wm_adsp2_ops[0];
		break;
	case 1:
		dsp->ops = &wm_adsp2_ops[1];
		break;
	default:
		dsp->ops = &wm_adsp2_ops[2];
		break;
	}

	INIT_WORK(&dsp->boot_work, wm_adsp_boot_work);

	return 0;
}