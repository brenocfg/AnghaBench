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
struct intel_sst_drv {int /*<<< orphan*/  dev; int /*<<< orphan*/  ddr_base; int /*<<< orphan*/  dram; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_dccm_config_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sst_post_download_mrfld(struct intel_sst_drv *ctx)
{
	sst_dccm_config_write(ctx->dram, ctx->ddr_base);
	dev_dbg(ctx->dev, "config written to DCCM\n");
}