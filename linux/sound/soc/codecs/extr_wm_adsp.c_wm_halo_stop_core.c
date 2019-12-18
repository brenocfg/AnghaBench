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
 scalar_t__ HALO_CCM_CORE_CONTROL ; 
 int /*<<< orphan*/  HALO_CORE_EN ; 
 scalar_t__ HALO_CORE_SOFT_RESET ; 
 int /*<<< orphan*/  HALO_CORE_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm_halo_stop_core(struct wm_adsp *dsp)
{
	regmap_update_bits(dsp->regmap, dsp->base + HALO_CCM_CORE_CONTROL,
			   HALO_CORE_EN, 0);

	/* reset halo core with CORE_SOFT_RESET */
	regmap_update_bits(dsp->regmap, dsp->base + HALO_CORE_SOFT_RESET,
			   HALO_CORE_SOFT_RESET_MASK, 1);
}