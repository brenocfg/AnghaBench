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
struct wm_adsp {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADSP2_CONTROL ; 
 int /*<<< orphan*/  ADSP2_SYS_ENA ; 
 int regmap_update_bits_async (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm_adsp2v2_enable_core (struct wm_adsp*) ; 

__attribute__((used)) static int wm_adsp2_enable_core(struct wm_adsp *dsp)
{
	int ret;

	ret = regmap_update_bits_async(dsp->regmap, dsp->base + ADSP2_CONTROL,
				       ADSP2_SYS_ENA, ADSP2_SYS_ENA);
	if (ret != 0)
		return ret;

	return wm_adsp2v2_enable_core(dsp);
}