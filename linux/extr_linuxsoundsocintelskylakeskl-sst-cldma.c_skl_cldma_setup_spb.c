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
 int /*<<< orphan*/  CL_SPBFIFO_SPBFCCTL_SPIBE (int) ; 
 int /*<<< orphan*/  CL_SPBFIFO_SPBFCCTL_SPIBE_MASK ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SPBFIFO_SPBFCCTL ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SPBFIFO_SPIB ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_write_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void skl_cldma_setup_spb(struct sst_dsp  *ctx,
		unsigned int size, bool enable)
{
	if (enable)
		sst_dsp_shim_update_bits_unlocked(ctx,
				SKL_ADSP_REG_CL_SPBFIFO_SPBFCCTL,
				CL_SPBFIFO_SPBFCCTL_SPIBE_MASK,
				CL_SPBFIFO_SPBFCCTL_SPIBE(1));

	sst_dsp_shim_write_unlocked(ctx, SKL_ADSP_REG_CL_SPBFIFO_SPIB, size);
}