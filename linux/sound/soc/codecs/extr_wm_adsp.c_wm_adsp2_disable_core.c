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
 scalar_t__ ADSP2_RDMA_CONFIG_1 ; 
 int /*<<< orphan*/  ADSP2_SYS_ENA ; 
 scalar_t__ ADSP2_WDMA_CONFIG_1 ; 
 scalar_t__ ADSP2_WDMA_CONFIG_2 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm_adsp2_disable_core(struct wm_adsp *dsp)
{
	regmap_write(dsp->regmap, dsp->base + ADSP2_RDMA_CONFIG_1, 0);
	regmap_write(dsp->regmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	regmap_write(dsp->regmap, dsp->base + ADSP2_WDMA_CONFIG_2, 0);

	regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
			   ADSP2_SYS_ENA, 0);
}