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
 int SST_CSR_24MHZ_LPCS ; 
 int SST_CSR_STALL ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hsw_stall(struct sst_dsp *sst)
{
	/* stall DSP */
	sst_dsp_shim_update_bits(sst, SST_CSR,
		SST_CSR_24MHZ_LPCS | SST_CSR_STALL,
		SST_CSR_STALL | SST_CSR_24MHZ_LPCS);
}