#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skl_sst {TYPE_2__* dsp; int /*<<< orphan*/  ipc; int /*<<< orphan*/  lib_count; int /*<<< orphan*/  lib_info; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; scalar_t__ fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 int /*<<< orphan*/  skl_freeup_uuid_list (struct skl_sst*) ; 
 int /*<<< orphan*/  skl_ipc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_release_library (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void bxt_sst_dsp_cleanup(struct device *dev, struct skl_sst *ctx)
{

	skl_release_library(ctx->lib_info, ctx->lib_count);
	if (ctx->dsp->fw)
		release_firmware(ctx->dsp->fw);
	skl_freeup_uuid_list(ctx);
	skl_ipc_free(&ctx->ipc);
	ctx->dsp->ops->free(ctx->dsp);
}