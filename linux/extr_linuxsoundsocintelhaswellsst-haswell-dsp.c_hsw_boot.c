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
 int /*<<< orphan*/  SST_CSR ; 
 int /*<<< orphan*/  SST_CSR_STALL ; 
 int /*<<< orphan*/  SST_HMDC ; 
 int SST_HMDC_HDDA_E0_ALLCH ; 
 int SST_HMDC_HDDA_E1_ALLCH ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hsw_boot(struct sst_dsp *sst)
{
	/* set oportunistic mode on engine 0,1 for all channels */
	sst_dsp_shim_update_bits(sst, SST_HMDC,
			SST_HMDC_HDDA_E0_ALLCH | SST_HMDC_HDDA_E1_ALLCH, 0);

	/* set DSP to RUN */
	sst_dsp_shim_update_bits_unlocked(sst, SST_CSR, SST_CSR_STALL, 0x0);
}