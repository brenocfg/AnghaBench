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
 int SST_BYT_CSR_RST ; 
 int SST_BYT_CSR_STALL ; 
 int SST_BYT_CSR_VECTOR_SEL ; 
 int /*<<< orphan*/  SST_CSR ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits64 (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sst_byt_reset(struct sst_dsp *sst)
{
	/* put DSP into reset, set reset vector and stall */
	sst_dsp_shim_update_bits64(sst, SST_CSR,
		SST_BYT_CSR_RST | SST_BYT_CSR_VECTOR_SEL | SST_BYT_CSR_STALL,
		SST_BYT_CSR_RST | SST_BYT_CSR_VECTOR_SEL | SST_BYT_CSR_STALL);

	udelay(10);

	/* take DSP out of reset and keep stalled for FW loading */
	sst_dsp_shim_update_bits64(sst, SST_CSR, SST_BYT_CSR_RST, 0);
}