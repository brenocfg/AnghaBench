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
union config_status_reg_mrfld {int full; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; int /*<<< orphan*/  shim; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_CSR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 void* sst_shim_read64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_shim_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int intel_sst_reset_dsp_mrfld(struct intel_sst_drv *sst_drv_ctx)
{
	union config_status_reg_mrfld csr;

	dev_dbg(sst_drv_ctx->dev, "sst: Resetting the DSP in mrfld\n");
	csr.full = sst_shim_read64(sst_drv_ctx->shim, SST_CSR);

	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);

	csr.full |= 0x7;
	sst_shim_write64(sst_drv_ctx->shim, SST_CSR, csr.full);
	csr.full = sst_shim_read64(sst_drv_ctx->shim, SST_CSR);

	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);

	csr.full &= ~(0x1);
	sst_shim_write64(sst_drv_ctx->shim, SST_CSR, csr.full);

	csr.full = sst_shim_read64(sst_drv_ctx->shim, SST_CSR);
	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);
	return 0;
}