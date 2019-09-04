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
 int /*<<< orphan*/  SKL_ADSPIC_CL_DMA ; 
 int /*<<< orphan*/  SKL_ADSP_REG_ADSPIC ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void skl_cldma_int_disable(struct sst_dsp *ctx)
{
	sst_dsp_shim_update_bits_unlocked(ctx,
			SKL_ADSP_REG_ADSPIC, SKL_ADSPIC_CL_DMA, 0);
}