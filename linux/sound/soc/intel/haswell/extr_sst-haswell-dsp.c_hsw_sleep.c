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
struct sst_dsp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_CSR ; 
 int SST_CSR_24MHZ_LPCS ; 
 int SST_CSR_RST ; 
 int SST_CSR_STALL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hsw_set_dsp_D3 (struct sst_dsp*) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hsw_sleep(struct sst_dsp *sst)
{
	dev_dbg(sst->dev, "HSW_PM dsp runtime suspend\n");

	/* put DSP into reset and stall */
	sst_dsp_shim_update_bits(sst, SST_CSR,
		SST_CSR_24MHZ_LPCS | SST_CSR_RST | SST_CSR_STALL,
		SST_CSR_RST | SST_CSR_STALL | SST_CSR_24MHZ_LPCS);

	hsw_set_dsp_D3(sst);
	dev_dbg(sst->dev, "HSW_PM dsp runtime suspend exit\n");
}