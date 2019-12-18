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
 scalar_t__ HALO_WDT_CONTROL ; 
 int /*<<< orphan*/  HALO_WDT_EN_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm_halo_stop_watchdog(struct wm_adsp *dsp)
{
	regmap_update_bits(dsp->regmap, dsp->base + HALO_WDT_CONTROL,
			   HALO_WDT_EN_MASK, 0);
}