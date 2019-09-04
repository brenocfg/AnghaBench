#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct skl_sst {TYPE_4__* dsp; scalar_t__ boot_complete; int /*<<< orphan*/  ipc; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* cl_cleanup_controller ) (TYPE_4__*) ;} ;
struct TYPE_10__ {TYPE_2__ ops; } ;
struct TYPE_11__ {TYPE_3__ cl_dev; TYPE_1__* ops; scalar_t__ fw; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* free ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 int /*<<< orphan*/  skl_cldma_int_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  skl_clear_module_table (TYPE_4__*) ; 
 int /*<<< orphan*/  skl_freeup_uuid_list (struct skl_sst*) ; 
 int /*<<< orphan*/  skl_ipc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

void skl_sst_dsp_cleanup(struct device *dev, struct skl_sst *ctx)
{

	if (ctx->dsp->fw)
		release_firmware(ctx->dsp->fw);
	skl_clear_module_table(ctx->dsp);
	skl_freeup_uuid_list(ctx);
	skl_ipc_free(&ctx->ipc);
	ctx->dsp->ops->free(ctx->dsp);
	if (ctx->boot_complete) {
		ctx->dsp->cl_dev.ops.cl_cleanup_controller(ctx->dsp);
		skl_cldma_int_disable(ctx->dsp);
	}
}